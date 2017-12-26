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

#define VAO_ENABLE_VERTEX_ATTRIBUTE(AttributeName, Size, OpenGLType, bNormalized, Program) \
{ \
	const int32 Attribute = glGetAttribLocation(Program, "In" PREPROCESSOR_TO_STRING(AttributeName)); \
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

   FORCEINLINE static bool Load(FStaticMesh* OutStaticMesh,
                                uint32 Program,
                                const FVertex* Vertices,
                                const uint16 VertexCount,
                                const uint16* Indices,
                                const uint16 IndexCount)
   {
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

uint32 CompileShaderFile(const TCHAR* FileName, const GLenum ShaderType)
{
   const DWORD NumberOfBytesToRead = 2048;

   CHAR* FileContent = new CHAR[NumberOfBytesToRead];
   DWORD NumberOfBytesRead = 0;

   HANDLE FileHandle = CreateFile(FileName,
                                  GENERIC_READ,
                                  FILE_SHARE_READ,
                                  NULL,
                                  OPEN_EXISTING,
                                  FILE_ATTRIBUTE_NORMAL,
                                  NULL);

   if (FileHandle == INVALID_HANDLE_VALUE)
   {
      LE_DebugLog(TEXT("Arquivo \'%s\' não encontrado.\n"), FileName);
   }

   if (ReadFile(FileHandle, FileContent, NumberOfBytesToRead - 1, &NumberOfBytesRead, NULL) == FALSE)
   {
      LE_DebugLog(TEXT("Erro ao ler o arquivo \'%s\'.\n"), FileName);
   }

   CloseHandle(reinterpret_cast<HANDLE>(FileHandle));

   if (NumberOfBytesRead > 0 && NumberOfBytesRead <= NumberOfBytesToRead - 1)
   {
      FileContent[NumberOfBytesRead] = '\0';
   }

   uint32 Shader = glCreateShader(ShaderType);
   glShaderSource(Shader, 1, &FileContent, (GLint*)&NumberOfBytesRead);
   glCompileShader(Shader);

   delete[] FileContent;

   return Shader;
}

void LoadShader(const TCHAR* VertexShaderFileName,
                const TCHAR* FragmentShaderFileName,
                uint32* OutVertexShader,
                uint32* OutFragmentShader,
                uint32* OutShader)
{
   *OutVertexShader = CompileShaderFile(VertexShaderFileName, GL_VERTEX_SHADER);
   *OutFragmentShader = CompileShaderFile(FragmentShaderFileName, GL_FRAGMENT_SHADER);

   *OutShader = glCreateProgram();

   glAttachShader(*OutShader, *OutVertexShader);
   glAttachShader(*OutShader, *OutFragmentShader);

   glLinkProgram(*OutShader);

   int32 bIsLinked;

   glGetProgramiv(*OutShader, GL_LINK_STATUS, &bIsLinked);

   if (!bIsLinked)
   {
      static CHAR* Error = new CHAR[512];
      int32 ErrorLength;

      glGetProgramInfoLog(*OutShader, sizeof(Error), &ErrorLength, Error);

      LE_DebugLog(Error);

      delete[] Error;
   }
}

uint32 LoadTexture(const CHAR* TextureName)
{
   const uint32 Flags = SOIL_FLAG_MIPMAPS | SOIL_FLAG_INVERT_Y | SOIL_FLAG_NTSC_SAFE_RGB | SOIL_FLAG_COMPRESS_TO_DXT;

   return SOIL_load_OGL_texture(TextureName, SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID, Flags);
}

/*----------------------------------------------------------------------------
         Globals.
----------------------------------------------------------------------------*/

HWND GWindowHandle;
HDC GDeviceContextHandle;
HGLRC GOpenGLContextHandle;

FStaticMesh GStaticMesh;

double GTime = 0;
double GStartTime = FPlatformTime::InitTiming();

float GKeyPressedTime[0xFF];
float GKeyRealesedTime[0xFF];
bool GKeyIsPressed[0xFF];

/*----------------------------------------------------------------------------
         Input.
----------------------------------------------------------------------------*/

FORCEINLINE bool IsKeyPressed(const WPARAM VirtualKeyCode)
{
   return GKeyIsPressed[VirtualKeyCode];
}

FORCEINLINE bool IsKeyUp(const WPARAM VirtualKeyCode)
{
   return GKeyRealesedTime[VirtualKeyCode] == GTime;
}

FORCEINLINE bool IsKeyDown(const WPARAM VirtualKeyCode)
{
   return GKeyPressedTime[VirtualKeyCode] == GTime;
}

/*----------------------------------------------------------------------------
         Forward Declarations.
----------------------------------------------------------------------------*/

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
void LoadMesh(uint32);

/*----------------------------------------------------------------------------
         MainLoop.
----------------------------------------------------------------------------*/

FORCEINLINE void MainLoop()
{
   bool bQuit = false;
   MSG Message;

   glEnable(GL_DEPTH_TEST);
   glEnable(GL_CULL_FACE);

   uint32 VertexShader, FragmentShader, Shader;
   LoadShader(TEXT("Shaders/VertexShader.vert"), TEXT("Shaders/FragmentShader.frag"), &VertexShader, &FragmentShader, &Shader);
   LoadMesh(Shader);
   const uint32 Texture = LoadTexture("Assets/Texture.png");

   const int32 TextureLocation = glGetUniformLocation(Shader, "_Texture");
   const int32 ModelViewProjectionMatrixLocation = glGetUniformLocation(Shader, "_ModelViewProjectionMatrix");
   const int32 ObjectMatrixLocation = glGetUniformLocation(Shader, "_ObjectMatrix");
   const int32 TimeLocation = glGetUniformLocation(Shader, "_Time");
   const int32 LightPosLocation = glGetUniformLocation(Shader, "_LightPos");

   glUniform1i(TextureLocation, 0);
   glActiveTexture(GL_TEXTURE0);
   glBindTexture(0, Texture);

   double LastUpdateTime = 0;
   double LastFixedUpdateTime = 0;
   float DeltaTime = 0;

   FMatrix ProjectionMatrix = FPerspectiveMatrix(FMath::Pi / 3, 1280, 720, 1, 1000);

   FVector CameraPosition(0, 0, 0);
   FVector CameraRotation(0, 0, 0);

   POINT Point;
   GetCursorPos(&Point);
   ScreenToClient(GWindowHandle, &Point);

   FVector2 MouseDelta(0, 0);
   FVector2 PrevMousePositon(Point.x, Point.y);
   FVector2 MousePosition(Point.x, Point.y);

   glUseProgram(Shader);

   while (!bQuit)
   {
      GTime += DeltaTime;

      if (PeekMessage(&Message, NULL, 0, 0, PM_REMOVE))
      {
         if (Message.message == WM_QUIT)
         {
            bQuit = true;
         }
         else if (Message.message == WM_KEYUP)
         {
            GKeyIsPressed[Message.wParam] = false;
            GKeyRealesedTime[Message.wParam] = GTime;
         }
         else if (Message.message == WM_KEYDOWN && !GKeyIsPressed[Message.wParam])
         {
            GKeyIsPressed[Message.wParam] = true;
            GKeyPressedTime[Message.wParam] = GTime;
         }
         else if (Message.message == WM_MOUSEMOVE)
         {
            MousePosition = FVector2(((int)(short)LOWORD(Message.lParam)), ((int)(short)HIWORD(Message.lParam)));
         }
         else
         {
            TranslateMessage(&Message);
            DispatchMessage(&Message);
         }
      }

      MouseDelta = MousePosition - PrevMousePositon;

      if (GTime - LastFixedUpdateTime > 0.02)
      {
         LastFixedUpdateTime = GTime;
      }

      glClearColor(50 / 255.0f, 76 / 255.0f, 88 / 255.0f, 0.0f);
      glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

      FVector Translation = FVector(0, 0, 0);

      if (IsKeyPressed('W'))
      {
         Translation.Z = 1;
      }
      else if (IsKeyPressed('S'))
      {
         Translation.Z = -1;
      }

      if (IsKeyPressed('A'))
      {
         Translation.X = -1;
      }
      else if (IsKeyPressed('D'))
      {
         Translation.X = 1;
      }

      CameraRotation.Y += MouseDelta.X * (720.0f / 1280.0f);
      CameraRotation.X += MouseDelta.Y;

      CameraRotation.X = FMath::Clamp(CameraRotation.X, -80.0f, 80.0f);

      FQuaternion CameraQuat = FQuaternion(CameraRotation.X, CameraRotation.Y, CameraRotation.Z);

      CameraPosition += CameraQuat * Translation.Normalize() * DeltaTime * 15;
      FMatrix ViewMatrix = CameraQuat * FTranslationMatrix(CameraPosition);

      FMatrix ObjectMatrix = FTranslationMatrix(0, 0, 15);
      FMatrix TransformMatrix = ObjectMatrix * ViewMatrix.Inverse() * ProjectionMatrix;

      glUniformMatrix4fv(ObjectMatrixLocation, 1, GL_TRUE, (GLfloat*)&ObjectMatrix);
      glUniformMatrix4fv(ModelViewProjectionMatrixLocation, 1, GL_TRUE, (GLfloat*)&TransformMatrix);
      glUniform4f(TimeLocation, GTime, 0, 0, 0);
      glUniform3f(LightPosLocation, CameraPosition.X, CameraPosition.Y, CameraPosition.Z);

      GStaticMesh.Draw();

      SwapBuffers(GDeviceContextHandle);

      PrevMousePositon = MousePosition;

   }

   glDeleteShader(VertexShader);
   glDeleteShader(FragmentShader);
   glDeleteProgram(Shader);
   glDeleteTextures(1, &Texture);
}

/*----------------------------------------------------------------------------
         WinMain.
----------------------------------------------------------------------------*/

int32 WINAPI WinMain(HINSTANCE InstanceHandle, HINSTANCE PrevInstanceHandle, LPSTR CommandLine, int CommandShow)
{  
   memset(GKeyPressedTime, -2, sizeof(GKeyPressedTime));
   memset(GKeyRealesedTime, -1, sizeof(GKeyRealesedTime));

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
      const DWORD Style = (WS_POPUPWINDOW | WS_VISIBLE) & ~(WS_CAPTION | WS_THICKFRAME);

      FVector2 Size(1280, 720);
      FVector2 Position = FVector2(GetSystemMetrics(SM_CXSCREEN), GetSystemMetrics(SM_CYSCREEN)) / 2 - Size / 2;
      GWindowHandle = CreateWindow(ClassName, ClassName, Style, Position.X, Position.Y, Size.X, Size.Y, NULL, NULL, InstanceHandle, NULL);
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
      case WM_CLOSE:
         PostQuitMessage(0);
         return 0;

      case WM_KILLFOCUS:
         ZeroMemory(GKeyIsPressed, sizeof(GKeyIsPressed));
         return 0;

      default:
         return DefWindowProc(WinHandle, Message, WParam, LParam);
   }
}

void LoadMesh(uint32 Shader)
{
#include "Temp/MeshData.generated.inl"

   FStaticMesh::Load
   (
      &GStaticMesh, Shader,
      Vertices, TExtent<decltype(Vertices)>::Value,
      Indices, TExtent<decltype(Indices)>::Value
   );
}



