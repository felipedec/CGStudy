/*----------------------------------------------------------------------------
			Este c�digo pertence a um projeto pessoal,
			baseado no c�digo aberto da Unreal Engine,
			com o intuito de aprendizado. Apenas as
			estrutura b�sica das classes s�o semelhantes
			e as vezes iguais, j� os corpos de m�todos
			s�o implementa��es pr�prias do desenvolvedor
			deste projeto.
			
			Saiba mais:
			https://github.com/felipedec/LeafEngine
----------------------------------------------------------------------------*/

#include "CoreTypes.h"


/*----------------------------------------------------------------------------
			Estruturas tempor�rias.
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

	int32 Int32;

public:
	
	FORCEINLINE FColor32() = default;

	FORCEINLINE FColor32(const int32 Hex)
	{
		this->Int32 = Hex;
	}

};

struct FVertex
{
public:

	FVector Position, Normal;
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

class FMesh
{
private:

	GLuint VerticesBuffer = 0, IndicesBuffer = 0;

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
	}

	FORCEINLINE void Draw() const
	{
		glBindBuffer(GL_ARRAY_BUFFER, VerticesBuffer);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IndicesBuffer);

		glEnableClientState(GL_TEXTURE_COORD_ARRAY);
		glEnableClientState(GL_NORMAL_ARRAY);
		glEnableClientState(GL_VERTEX_ARRAY);
		glEnableClientState(GL_COLOR_ARRAY);

		glTexCoordPointer(2, GL_FLOAT, sizeof(FVertex), (void*)offsetof(FVertex, TexCoord0));
		glNormalPointer(GL_FLOAT, sizeof(FVertex), (void*)offsetof(FVertex, Normal));
		glVertexPointer(3, GL_FLOAT, sizeof(FVertex), (void*)offsetof(FVertex, Position));
		glColorPointer(4, GL_UNSIGNED_BYTE, sizeof(FVertex), (void*)offsetof(FVertex, Color));

		glDrawElements(GL_TRIANGLES, Indices.size(), GL_UNSIGNED_SHORT, NULL);

		glDisableClientState(GL_TEXTURE_COORD_ARRAY);
		glDisableClientState(GL_NORMAL_ARRAY);
		glDisableClientState(GL_VERTEX_ARRAY);
		glDisableClientState(GL_COLOR_ARRAY);

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
	float theta = 0.0F;

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
			glClearColor(1.0f, 0.0f, 0.0f, 0.0f);
			glClear(GL_COLOR_BUFFER_BIT);

			glPushMatrix();

			glRotatef(theta, 0.0f, 0.0f, 1.0f);
		

			ExampleMesh.Draw();

			glPopMatrix();

			SwapBuffers(GDeviceContextHandle);

			theta += 0.1f;
			Sleep(1);
		}
	}
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

	// Exibir informa��es
	{
		LE_DebugLog(TEXT("Placa de v�deo: "));
		LE_DebugLog((CHAR*)glGetString(GL_RENDERER));
		LE_DebugLog("\n");

		LE_DebugLog(TEXT("Vers�o OpenGL: "));
		LE_DebugLog((CHAR*)glGetString(GL_VERSION));
		LE_DebugLog("\n");
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
