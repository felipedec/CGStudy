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

#include "GenericPlatform/GenericPlatformTimer.h"
#include "Windows/WindowsPlatform.h"
#include "Core.h"

/*----------------------------------------------------------------------------
			FGenericPlatformTimer.
----------------------------------------------------------------------------*/

struct FGenericPlatformTimer
{
public:
	
	FORCEINLINE virtual void Start() = 0;

	FORCEINLINE virtual float Stop() = 0;
};