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

enum ENativeConsoleTextColor : uint8
{
	Neutral,
	Error,
	Warning,
	Success,

	// Numeros de elementos enumerados
	Count
};

/**
 * Esta estrutura n�o chega ser usada, a utilidade dela � s� para servir como refer�ncia,
 * caso queira implementar o console nativo de uma plataforma � necass�rio que a estrutura 
 * possua todos os metodos assim como nesta estrutura.
 */
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
