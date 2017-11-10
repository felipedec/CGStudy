/*----------------------------------------------------------------------------
			Este código pertence a um projeto pessoal,
			baseado no código aberto da Unreal Engine,
			com o intuito de aprendizado. Apenas as
			estrutura básica das classes são semelhantes
			e as vezes iguais, já os corpos de métodos
			são implementações próprias do desenvolvedor
			deste projeto.
			
			Saiba mais:
			https://github.com/felipedec/LeafEngine
----------------------------------------------------------------------------*/

#include "CoreTypes.h"


/*----------------------------------------------------------------------------
			Estruturas temporárias.
----------------------------------------------------------------------------*/

#include <vector>

union FColor32
{
public:

	struct
	{
		int8 R, G, B, A;
	};

	int8 Components[4];

	uint32 Int32;

public:
	
	FORCEINLINE FColor32() = default;

	FORCEINLINE FColor32(const uint32 Hex)
	{
		this->Int32 = Hex;
	}

};

struct FVertex
{
public:

	FVector Position;
	FVector Normal;
	FVector2 TexCoord0;
	FColor32 Color;

public:

	FORCEINLINE FVertex(const FVector& InPosition, const FVector& InNormal, const FVector2& InTexCoord0, const FColor32& InColor) :
		Position(InPosition),
		Normal(InNormal),
		TexCoord0(InTexCoord0),
		Color(InColor)
	{

	}
};

#define FVERTEX_MEMBER_OFFSET(Member)  ((void*)offsetof(FVertex, Member))

class FMesh
{
private:

	GLuint VerticesBuffer = 0, IndicesBuffer = 0;

	bool bCanDraw = false;

public:

	std::vector<int16> Indices;
	std::vector<FVertex> Vertices;

public:

	FORCEINLINE ~FMesh()
	{
		DeleteBuffers();
	}

public:

	FORCEINLINE void DeleteBuffers()
	{
		if (VerticesBuffer || IndicesBuffer)
		{
			bCanDraw = false;

			glDeleteBuffers(1, &VerticesBuffer);
			glDeleteBuffers(1, &IndicesBuffer);
		}
	}
	
	FORCEINLINE void CreateVBOs()
	{
		DeleteBuffers();

		if (Indices.size() == 0 || Vertices.size() == 0)
		{
			return;
		}

		glGenBuffers(1, &VerticesBuffer);
		glBindBuffer(GL_ARRAY_BUFFER, VerticesBuffer);
		glBufferData(GL_ARRAY_BUFFER, sizeof(FVertex) * Vertices.size(), Vertices.data(), GL_STATIC_DRAW);

		glGenBuffers(1, &IndicesBuffer);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IndicesBuffer);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(int16) * Indices.size(), Indices.data(), GL_STATIC_DRAW);

		bCanDraw = true;
	}

	FORCEINLINE void Draw(GLuint Program, const int32 PositionAttr, const int32 NormalAttr, const int32 ColorAttr, const int TexCoord0Attr) const
	{
		glBindBuffer(GL_ARRAY_BUFFER, VerticesBuffer);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IndicesBuffer);

		glVertexAttribPointer(PositionAttr, 3, GL_FLOAT, GL_FALSE, sizeof(FVertex), FVERTEX_MEMBER_OFFSET(Position));
		glEnableVertexAttribArray(PositionAttr);

		glVertexAttribPointer(NormalAttr, 3, GL_FLOAT, GL_TRUE, sizeof(FVertex), FVERTEX_MEMBER_OFFSET(Normal));
		glEnableVertexAttribArray(NormalAttr);

		glVertexAttribPointer(ColorAttr, 4, GL_UNSIGNED_BYTE, GL_FALSE, sizeof(FVertex), FVERTEX_MEMBER_OFFSET(Color));
		glEnableVertexAttribArray(ColorAttr);

		glVertexAttribPointer(TexCoord0Attr, 2, GL_FLOAT, GL_FALSE, sizeof(FVertex), FVERTEX_MEMBER_OFFSET(TexCoord0));
		glEnableVertexAttribArray(TexCoord0Attr);

		glUseProgram(Program);

		glDrawElements(GL_TRIANGLES, Indices.size(), GL_UNSIGNED_SHORT, NULL);
	}
};


/*----------------------------------------------------------------------------
			Globals.
----------------------------------------------------------------------------*/

HWND GWindowHandle;
HDC GDeviceContextHandle;
HGLRC GOpenGLContextHandle;

FMesh ExampleMesh;

/*----------------------------------------------------------------------------
			Forward Declarations.
----------------------------------------------------------------------------*/

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);

/*----------------------------------------------------------------------------
			MainLoop.
----------------------------------------------------------------------------*/

FORCEINLINE void MainLoop()
{
	bool bQuit = false;
	MSG Message;


	GLuint VertexShader = glCreateShader(GL_VERTEX_SHADER);
	{
		static const char* VertexShaderSource = 
		"																								\n\
			#version 430																			\n\
			layout(location = 0) uniform mat4 ModelViewPorjectionMatrix;			\n\
																										\n\
			layout(location = 1) uniform vec4 InPosition;								\n\
			layout(location = 2) uniform vec3 InNormal;									\n\
			layout(location = 3) uniform vec2 InTexCoord0;								\n\
			layout(location = 4) uniform vec4 InColor;									\n\
																										\n\
			void main()																				\n\
			{																							\n\
				gl_Position = InPosition;														\n\
			}																							\n\
		";
		const int32 VertexShaderSourceLength = 544;

		glShaderSourceARB(VertexShader, 1, &VertexShaderSource, &VertexShaderSourceLength);
		glCompileShaderARB(VertexShader);
	}

	GLuint FragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	{
		const char* FragmentShaderSource = 
		"																								\n\
			#version 430																			\n\
			void main()																				\n\
			{																							\n\
				gl_FragColor = vec4(0.0, 0.4, 0.8, 1.0);									\n\
			}																							\n\
		";
		const int32 FragmentShaderSourceLength = 208;

		glShaderSourceARB(FragmentShader, 1, &FragmentShaderSource, &FragmentShaderSourceLength);
		glCompileShaderARB(FragmentShader);
	}

	GLuint Program = glCreateProgram();

	glAttachShader(Program, VertexShader);
	glAttachShader(Program, FragmentShader);

	glLinkProgramARB(Program);

	int32 bIsLinked;

	glGetProgramiv(Program, GL_LINK_STATUS, &bIsLinked);
	if (!bIsLinked)
	{
		GLchar Error[512];
		int32 ErrorLength;
		glGetProgramInfoLog(Program, sizeof(Error), &ErrorLength, Error);
		LE_DebugLogError(Error);
	}

	int32 VertexPositionAttribute = glGetUniformLocation(Program, "InPosition");
	int32 VertexNormalAttribute = glGetUniformLocation(Program, "InNormal");
	int32 VertexColorAttribute = glGetUniformLocation(Program, "InColor");
	int32 VertexTexCoord0Attribute = glGetUniformLocation(Program, "InTexCoord0");

	FMatrix ModelMatrix = FQuaternion(0, 30, 0) * FTranslationMatrix(0.01f, 0.1f, 0.2f);

	while (!bQuit)
	{
		if (PeekMessage(&Message, NULL, 0, 0, PM_REMOVE))
		{
			if (Message.message == WM_QUIT)
			{
				bQuit = true;
			}
			else
			{
				TranslateMessage(&Message);
				DispatchMessage(&Message);
			}
		}
		else
		{
			glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
			glClear(GL_COLOR_BUFFER_BIT);

			ExampleMesh.Draw
			(
				Program, 
				VertexPositionAttribute,
				VertexNormalAttribute,
				VertexColorAttribute,
				VertexTexCoord0Attribute
			);

			SwapBuffers(GDeviceContextHandle);

			Sleep(1);
		}
	}

	glDetachShader(Program, VertexShader);
	glDetachShader(Program, FragmentShader);

	glDeleteShader(VertexShader);
	glDeleteShader(FragmentShader);

	glDeleteProgram(Program);
}

/*----------------------------------------------------------------------------
			WinMain.
----------------------------------------------------------------------------*/

int32 WINAPI WinMain(HINSTANCE InstanceHandle, HINSTANCE PrevInstanceHandle, LPSTR CommandLine, int CommandShow)
{
	// Registrar a classe do Windows
	{
		const TCHAR* ClassName = TEXT("LeafEngine");

		WNDCLASS WinClass;
		ZeroMemory(&WinClass, sizeof(WinClass));

		WinClass.style = CS_OWNDC;
		WinClass.lpfnWndProc = WndProc;
		WinClass.hInstance = InstanceHandle;
		WinClass.hIcon = LoadIcon(NULL, IDI_APPLICATION);
		WinClass.hCursor = LoadCursor(NULL, IDC_ARROW);
		WinClass.hbrBackground = (HBRUSH)GetStockObject(BLACK_BRUSH);
		WinClass.lpszMenuName = NULL;
		WinClass.lpszClassName = ClassName;

		RegisterClass(&WinClass);
	}

	// Criar janela
	{
		const TCHAR* ClassName = TEXT("LeafEngine");
		const TCHAR* WindowName = TEXT("GameName");
		const DWORD Style = WS_CAPTION | WS_POPUPWINDOW | WS_VISIBLE;

		GWindowHandle = CreateWindow(ClassName, WindowName, Style, 0, 0, 1280, 720, NULL, NULL, InstanceHandle, NULL);
	}

	// Criar Contexto OpenGL
	{
		GDeviceContextHandle = GetDC(GWindowHandle);

		PIXELFORMATDESCRIPTOR PixelFormatDescriptor;
		ZeroMemory(&PixelFormatDescriptor, sizeof(PixelFormatDescriptor));

		PixelFormatDescriptor.nSize = sizeof(PixelFormatDescriptor);
		PixelFormatDescriptor.nVersion = 1;
		PixelFormatDescriptor.dwFlags = PFD_DRAW_TO_WINDOW | PFD_SUPPORT_OPENGL | PFD_DOUBLEBUFFER;
		PixelFormatDescriptor.iPixelType = PFD_TYPE_RGBA;
		PixelFormatDescriptor.cColorBits = 24;
		PixelFormatDescriptor.cDepthBits = 16;
		PixelFormatDescriptor.iLayerType = PFD_MAIN_PLANE;

		int32 Format = ChoosePixelFormat(GDeviceContextHandle, &PixelFormatDescriptor);
		SetPixelFormat(GDeviceContextHandle, Format, &PixelFormatDescriptor);

		GOpenGLContextHandle = wglCreateContext(GDeviceContextHandle);
		wglMakeCurrent(GDeviceContextHandle, GOpenGLContextHandle);
	}

	// Exibir informações
	{
		LE_DebugLog(TEXT("%-36sVersão OpenGL:\n"), TEXT("Placa de vídeo:"));
		LE_DebugLog("%-36s%s\n", glGetString(GL_RENDERER), glGetString(GL_VERSION));
	}

	// Iniciar Glew
	if (glewInit() != GLEW_OK)
	{
		goto DestroyContextAndClose;
	}

	// Definir objeto de exemplo
	{
		ExampleMesh.Indices = { 0, 1, 2 };
		ExampleMesh.Vertices =
		{
			FVertex(FVector(0.0f, 1.0f, 0.0f), FVector::Forward, FVector2::Zero, 0xFF00FF00),
			FVertex(FVector(0.87f, -0.5f, 0.0f), FVector::Forward, FVector2::Zero, 0xFFFFFFFF),
			FVertex(FVector(-0.87f, -0.5f, 0.0f), FVector::Forward, FVector2::Zero, 0x00FFFFFF),
		};
		ExampleMesh.CreateVBOs();
	}

	// Loop principal
	MainLoop();

	// Destruir contexto OpenGL e a janela
	DestroyContextAndClose:
	{
		wglMakeCurrent(NULL, NULL);
		wglDeleteContext(GOpenGLContextHandle);
		ReleaseDC(GWindowHandle, GDeviceContextHandle);
		DestroyWindow(GWindowHandle);
	}

	return 0;
}

/*----------------------------------------------------------------------------
			Window Procedure Callback.
----------------------------------------------------------------------------*/

LRESULT CALLBACK WndProc(HWND WinHandle, UINT Message, WPARAM WParam, LPARAM LParam)
{
	switch (Message)
	{
	case WM_CREATE:
		return 0;

	case WM_CLOSE:
		PostQuitMessage(0);
		return 0;

	case WM_DESTROY:
		return 0;

	case WM_KEYDOWN:
		switch (WParam)
		{
		case VK_ESCAPE:
			PostQuitMessage(0);
			return 0;
		}
		return 0;
		
	default:
		return DefWindowProc(WinHandle, Message, WParam, LParam);
	}
}
