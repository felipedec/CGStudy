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

template <int32 Size, uint32 Alignment> struct TAlignedBytes;

template <int32 Size>
struct TAlignedBytes<Size, 1>
{
	uint8 Pad[Size];
};

#define IMPLEMENT_ALIGNED_STORAGE(Align) \
	template<int32 Size> \
	struct TAlignedBytes<Size, Align> \
	{ \
		struct MS_ALIGN(Align) TPadding \
		{ \
			uint8 Pad[Size]; \
		} GCC_ALIGN(Align); \
		TPadding Padding; \
	}; \

IMPLEMENT_ALIGNED_STORAGE(16); 
IMPLEMENT_ALIGNED_STORAGE(8);
IMPLEMENT_ALIGNED_STORAGE(4);
IMPLEMENT_ALIGNED_STORAGE(2);

template <typename TElement, uint32 NumElements, uint32 Alignment = alignof(TElement)>
class TStaticArray
{
private:

	TAlignedBytes<sizeof(TElement), Alignment> Elements[NumElements];

public:

	TStaticArray()
	{
		for (uint32 ElementIndex = 0; ElementIndex < NumElements; ++ElementIndex)
		{
			new(&(*this)[ElementIndex]) TElement;
		}
	}

public:

	FORCEINLINE TElement& operator[](uint32 Index)
	{
		check(Index < NumElements);
		return *(TElement*)&Elements[Index];
	}

	FORCEINLINE const TElement& operator[](uint32 Index) const
	{
		check(Index < NumElements);
		return *(const TElement*)&Elements[Index];
	}

public:

	FORCEINLINE int32 Num() const 
	{ 
		return NumElements;
	}
};


#define VAO_ENABLE_VERTEX_ATTRIBUTE(AttributeName, Size, OpenGLType, bNormalized, Program) \
{ \
	int32 Attribute = glGetAttribLocation(Program, "In" PREPROCESSOR_TO_STRING(AttributeName)); \
	if (Attribute >= 0) \
	{ \
		glEnableVertexAttribArray(Attribute); \
		const void* Offset = ((void*)offsetof(FVertex, AttributeName)); \
		glVertexAttribPointer(Attribute, Size, OpenGLType, bNormalized, sizeof(FVertex), Offset); \
	} \
} \

class FStaticMesh
{
private:

	uint32 VertexBufferObject;
	uint32 VertexArrayObject;
	uint32 IndexBufferObject;
	uint16 VertexCount;
	uint16 IndexCount;

public:

	FORCEINLINE ~FStaticMesh()
	{
		Unload();
	}

private:

	FORCEINLINE void Unload()
	{
		if (VertexArrayObject > 0)
		{
			glDeleteVertexArrays(1, &VertexArrayObject);
		}

		if (VertexBufferObject > 0)
		{
			glDeleteBuffers(1, &VertexBufferObject);
		}

		if (IndexBufferObject > 0)
		{
			glDeleteBuffers(1, &IndexBufferObject);
		}
	}

public:

	FORCEINLINE static bool Load(FStaticMesh* OutStaticMesh, uint32 Program, const FVertex* Vertices, const uint16 VertexCount, const uint16* Indices, const uint16 IndexCount)
	{
		check((VertexCount == 0 || IndexCount == 0) || IndexCount % 3 > 0)

		OutStaticMesh->IndexCount = IndexCount; 
		OutStaticMesh->VertexCount = IndexCount;

		// VertexArrayObject
		glGenVertexArrays(1, &OutStaticMesh->VertexArrayObject);
		glBindVertexArray(OutStaticMesh->VertexArrayObject);

		// VertexBufferObject
		glGenBuffers(1, &OutStaticMesh->VertexBufferObject);
		glBindBuffer(GL_ARRAY_BUFFER, OutStaticMesh->VertexBufferObject);
		glBufferData(GL_ARRAY_BUFFER, sizeof(FVertex) * VertexCount, Vertices, GL_STATIC_DRAW);

		// IndexBufferObject
		glGenBuffers(1, &OutStaticMesh->IndexBufferObject);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, OutStaticMesh->IndexBufferObject);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(uint16) * IndexCount, Indices, GL_STATIC_DRAW);

		// Vertex Attributes
		VAO_ENABLE_VERTEX_ATTRIBUTE(Position, 3, GL_FLOAT, GL_FALSE, Program);
		VAO_ENABLE_VERTEX_ATTRIBUTE(Normal, 3, GL_FLOAT, GL_TRUE, Program);
		VAO_ENABLE_VERTEX_ATTRIBUTE(Color, 4, GL_UNSIGNED_BYTE, GL_TRUE, Program);
		VAO_ENABLE_VERTEX_ATTRIBUTE(TexCoord0, 2, GL_FLOAT, GL_FALSE, Program);

		glBindVertexArray(0);

		return true;
	}

	FORCEINLINE void Draw() const
	{
		glBindVertexArray(VertexArrayObject);
		glDrawElements(GL_TRIANGLES, IndexCount, GL_UNSIGNED_SHORT, 0);
	}
};

	
/*----------------------------------------------------------------------------
			Globals.
----------------------------------------------------------------------------*/

HWND GWindowHandle;
HDC GDeviceContextHandle;
HGLRC GOpenGLContextHandle;

FStaticMesh GStaticMesh;

/*----------------------------------------------------------------------------
			Forward Declarations.
----------------------------------------------------------------------------*/

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);

/*----------------------------------------------------------------------------
			MainLoop.
----------------------------------------------------------------------------*/

#include <cstring>

FORCEINLINE void MainLoop()
{
	bool bQuit = false;
	MSG Message;
	 
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_CULL_FACE);

	//OFSTRUCT OpenFileInfo;

	//HFILE FileHandle = LZOpenFile(TEXT("Shader.shader"), &OpenFileInfo, OF_READ);

	//LZClose(FileHandle);

	uint32 VertexShader = glCreateShader(GL_VERTEX_SHADER);
	{
		static const char* VertexShaderSource =
			"																							\n\
			#version 400																			\n\
			uniform mat4 _ModelViewProjectionMatrix;										\n\
			uniform vec4 _Time;																	\n\
																										\n\
			in vec3 InPosition;																	\n\
			in vec3 InNormal;																		\n\
			in vec2 InTexCoord0;																	\n\
			in vec4 InColor;																		\n\
																										\n\
			struct v2f																				\n\
			{																							\n\
				vec4 Color;																			\n\
			};																							\n\
																										\n\
			out v2f VertexInfo;																	\n\
																										\n\
			void main()																				\n\
			{																							\n\
				VertexInfo.Color = InColor;													\n\
				gl_Position = vec4(InPosition, 1.0) * _ModelViewProjectionMatrix; \n\
			}																							\n\
		";
		const int32 VertexShaderSourceLength = strlen(VertexShaderSource);

		glShaderSource(VertexShader, 1, &VertexShaderSource, &VertexShaderSourceLength);
		glCompileShader(VertexShader);
	}

	uint32 FragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	{
		static const char* FragmentShaderSource =
			"																							\n\
			#version 400																			\n\
			uniform vec4 _Time;																	\n\
			out vec4 OutColor;																	\n\
			struct v2f																				\n\
			{																							\n\
				vec4 Color;																			\n\
			};																							\n\
																										\n\
			in v2f VertexInfo;																	\n\
			void main()																				\n\
			{																							\n\
				OutColor = VertexInfo.Color * abs(sin(_Time[0]));						\n\
			}																							\n\
		";
		const int32 FragmentShaderSourceLength = strlen(FragmentShaderSource);

		glShaderSource(FragmentShader, 1, &FragmentShaderSource, &FragmentShaderSourceLength);
		glCompileShader(FragmentShader);
	}


	uint32 Program = glCreateProgram();
	{
		glAttachShader(Program, VertexShader);
		glAttachShader(Program, FragmentShader);

		glLinkProgram(Program);

		int32 bIsLinked;

		glGetProgramiv(Program, GL_LINK_STATUS, &bIsLinked);
		if (!bIsLinked)
		{
			CHAR* Error = new CHAR[512];
			int32 ErrorLength;

			glGetProgramInfoLog(Program, sizeof(Error), &ErrorLength, Error);

			LE_DebugLogError(Error);

			delete[] Error;
			return;
		}
	}

	// Definir objeto de exemplo
	{
		const static uint16 Indices[] = 
		{ 
			0, 1, 2,
			2, 3, 0,
			4, 1, 0,
			4, 5, 1,
			7, 5, 4,
			7, 6, 5,
			2, 1, 6,
			5, 6, 1,
			6, 7, 2,
			2, 7, 3,
			0, 7, 4,
			0, 3, 7,
		};
		const static FVertex Vertices[] =
		{
			FVertex(FVector(4, 4, 4), FVector::Zero, FVector2::Zero, 0xFFFF0000),
			FVertex(FVector(4, -4, 4), FVector::Zero, FVector2::Zero, 0xFF00FF00),
			FVertex(FVector(-4, -4, 4), FVector::Zero, FVector2::Zero, 0xFF0000FF),
			FVertex(FVector(-4, 4, 4), FVector::Zero, FVector2::Zero, 0xFFFFFF00),

			FVertex(FVector(4, 4, -4), FVector::Zero, FVector2::Zero, 0xFFFF00FF),
			FVertex(FVector(4, -4, -4), FVector::Zero, FVector2::Zero, 0xFF00FFFF),
			FVertex(FVector(-4, -4, -4), FVector::Zero, FVector2::Zero, 0xFFFFFFFF),
			FVertex(FVector(-4, 4, -4), FVector::Zero, FVector2::Zero, 0xFF0F0F0F),
		}; 

		FStaticMesh::Load
		(
			&GStaticMesh, Program, 
			Vertices, TExtent<decltype(Vertices)>::Value,
			Indices, TExtent<decltype(Indices)>::Value
		);
	}
	
	int32 ModelViewProjectionMatrixLocation = glGetUniformLocation(Program, "_ModelViewProjectionMatrix");
	int32 TimeLocation = glGetUniformLocation(Program, "_Time");

	float DeltaTime = 0;
	float Time = 0;
	float LastTitleUpdateTime = 0;
	FPlatformTimer Timer;

	FMatrix ProjectionMatrix = FPerspectiveMatrix(FMath::Pi / 3 , 1280, 720, 1, 1000);


	while (!bQuit)
	{
		Timer.Start();
		Time += DeltaTime;

		if (Time - LastTitleUpdateTime > 0.5f)
		{
			TCHAR Buffer[96];
			int32 Characters = swprintf_s(Buffer, TEXT("%.4fms | %d FPS"), DeltaTime, (int)(1 / DeltaTime));
			SetWindowText(GWindowHandle, Buffer);

			LastTitleUpdateTime = Time;
		}

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
			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

			FMatrix ModelMatrix = FTranslationMatrix(0, 0, 33) 
										 * FQuaternion(Time * 90, 0, Time * 45)
										 * ProjectionMatrix;

			glUniformMatrix4fv(ModelViewProjectionMatrixLocation, 1, GL_TRUE, (GLfloat*)&ModelMatrix);
			glUniform4f(TimeLocation, Time, 0, 0, 0);

			glUseProgram(Program);

			GStaticMesh.Draw();

			SwapBuffers(GDeviceContextHandle);
		}
		
		DeltaTime = Timer.Stop();
	}

	glDeleteShader(VertexShader);
	glDeleteShader(FragmentShader);

	glDeleteProgram(Program);
}

/*----------------------------------------------------------------------------
			WinMain.
----------------------------------------------------------------------------*/

int32 WINAPI WinMain(HINSTANCE InstanceHandle, HINSTANCE PrevInstanceHandle, LPSTR CommandLine, int CommandShow)
{
	const TCHAR* ClassName = TEXT("LeafEngine");

	// Registrar a classe do Windows
	{

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

	// Iniciar Glew
	if (glewInit() != GLEW_OK)
	{
		goto DestroyContextAndClose;
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

	default:
		return DefWindowProc(WinHandle, Message, WParam, LParam);
	}
}