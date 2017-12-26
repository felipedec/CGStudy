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

#pragma once

#include "GenericPlatform/GenericPlatformConsoleWindow.h"
#include "Windows/WindowsPlatform.h"

class FWindowsConsoleWindow;
typedef FWindowsConsoleWindow FConsoleWindow;

/*----------------------------------------------------------------------------
			Variáveis Estátitcas.
----------------------------------------------------------------------------*/

/** Handle para o dispositivo de saída */
static HANDLE StdOutputConsoleHadle;

/** Buffer utilizado para formatar armazenar as string formatadas */
static union { TCHAR W[255]; CHAR A[512]; } Buffer;

/*----------------------------------------------------------------------------
			FWindowsConsoleWindow.
----------------------------------------------------------------------------*/

class FWindowsConsoleWindow : public FGenericPlatformConsoleWindow
{
private:

	FORCEINLINE static void Alloc()
	{
		AllocConsole();

		StdOutputConsoleHadle = GetStdHandle(STD_OUTPUT_HANDLE);
		SetConsoleTitleW(PREPROCESSOR_TO_STRINGW(FWindowsConsoleWindow));
	}
      
public:

	template <typename ...TArgs>
	FORCEINLINE static void Printf(const TCHAR* Format, const TArgs&... Args)
	{
      if (GetConsoleWindow() == NULL)
      { 
         Alloc();
      }

		int32 Characters = swprintf_s(Buffer.W, Format, Args...);

		WriteConsoleW(StdOutputConsoleHadle, Buffer.W, Characters, NULL, NULL);
		WriteConsoleW(StdOutputConsoleHadle, TEXT("\n"), 1, NULL, NULL);
	}

	template <typename ...TArgs>
	FORCEINLINE static void Printf(const CHAR* Format, const TArgs&... Args)
	{
      if (GetConsoleWindow() == NULL)
      { 
         Alloc();
      }

		int32 Characters = sprintf_s(Buffer.A, Format, Args...);

		WriteConsoleA(StdOutputConsoleHadle, Buffer.A, Characters, NULL, NULL);
		WriteConsoleA(StdOutputConsoleHadle, "\n", 1, NULL, NULL);
	}

	FORCEINLINE static void Close()	
	{
		FreeConsole();
	}
};

