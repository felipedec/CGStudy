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

#include "Core.h"

/*----------------------------------------------------------------------------
			ENativeConsoleTextColor.
----------------------------------------------------------------------------*/

enum ENativeConsoleTextColor : uint8
{
	Neutral,
	Error,
	Warning,
	Success,

	// Numeros de elementos enumerados
	Count
};

/*----------------------------------------------------------------------------
			FGenericPlatformNativeConsole.
----------------------------------------------------------------------------*/

class FGenericPlatformNativeConsole
{
public:

	CONSTEXPR static bool bSupportColoredText = false;

public:

	template <typename ...TArgs>
	FORCEINLINE static void Printf(ENativeConsoleTextColor Color, const TCHAR* Format, const TArgs&... Args) {};

	template <typename ...TArgs>
	FORCEINLINE static void Printf(ENativeConsoleTextColor Color, const CHAR* Format, const TArgs&... Args) {};

	FORCEINLINE static void Close() {};
};
