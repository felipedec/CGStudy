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