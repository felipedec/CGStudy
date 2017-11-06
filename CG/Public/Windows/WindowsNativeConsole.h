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

#pragma once

#include "GenericPlatform/GenericPlatformNativeConsole.h"

/*----------------------------------------------------------------------------
			Windows API Headers.
----------------------------------------------------------------------------*/

#include <stdio.h>
#include <io.h>
#include <fcntl.h>
#include <windows.h>
#include <strsafe.h>
#include <winbase.h>

/*----------------------------------------------------------------------------
			Vari�veis Est�titcas.
----------------------------------------------------------------------------*/

/** Tabela com os c�digo das cores do console do Windows */
static WORD WinColorsLookUpTable[ENativeConsoleTextColor::Count];
/** Handle para o dispositivo padr�o de sa�da */
static HANDLE StdOutputConsoleHadle;
/** Buffer utilizado para formatar armazenar as string formatadas */
static union { TCHAR Wide[255]; CHAR Ansi[512]; } Buffer;

/*----------------------------------------------------------------------------
			FWindowsNativeConsole.
----------------------------------------------------------------------------*/

class FWindowsNativeConsole : public FGenericPlatformNativeConsole
{
private:

	FORCEINLINE static void Alloc()
	{
		AllocConsole();

		StdOutputConsoleHadle = GetStdHandle(STD_OUTPUT_HANDLE);

		// Definir tabela de cores 
		{
			WinColorsLookUpTable[ENativeConsoleTextColor::Neutral] = 15;
			WinColorsLookUpTable[ENativeConsoleTextColor::Error] = 12;
			WinColorsLookUpTable[ENativeConsoleTextColor::Warning] = 14;
			WinColorsLookUpTable[ENativeConsoleTextColor::Success] = 10;
		}

		SetConsoleTitle(TEXT("Leaf Engine Debug Console"));
	}

	FORCEINLINE static void Prepare(ENativeConsoleTextColor Color)
	{
		if (GetConsoleWindow() == NULL)
		{
			Alloc();
		}

		if (Color >= ENativeConsoleTextColor::Count)
		{
			Color = ENativeConsoleTextColor::Neutral;
		}

		SetConsoleTextAttribute(StdOutputConsoleHadle, WinColorsLookUpTable[Color]);
	}

public:

	CONSTEXPR static bool bSupportColoredText = true;

public:

	template <typename ...TArgs>
	FORCEINLINE static void Printf(ENativeConsoleTextColor Color, const TCHAR* Format, const TArgs&... Args)
	{
		Prepare(Color);
		int32 Characters = swprintf_s(Buffer.Wide, Format, Args...);
		WriteConsoleW(StdOutputConsoleHadle, Buffer.Wide, Characters, NULL, NULL);
	}

	template <typename ...TArgs>
	FORCEINLINE static void Printf(ENativeConsoleTextColor Color, const CHAR* Format, const TArgs&... Args)
	{
		Prepare(Color);
		int32 Characters = sprintf_s(Buffer.Ansi, Format, Args...);
		WriteConsoleA(StdOutputConsoleHadle, Buffer.Ansi, Characters, NULL, NULL);
	}

	FORCEINLINE static void Close()
	{
		FreeConsole();
	}
};

