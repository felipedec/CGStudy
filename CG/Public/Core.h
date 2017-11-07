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

/*----------------------------------------------------------------------------
			Module.
----------------------------------------------------------------------------*/

#define CORE_API
#define FORCEINLINE __forceinline
#define CONSTEXPR constexpr

/*----------------------------------------------------------------------------
			Platform Macros.
----------------------------------------------------------------------------*/

#define USE_DIRECTX_MATH

/*----------------------------------------------------------------------------
			Includes.
----------------------------------------------------------------------------*/

#define GLEW_STATIC 

#pragma comment(lib, "opengl32.lib")
#pragma comment(lib, "glu32.lib")
#pragma comment(lib, "glew32s.lib")

#include <gl/glew.h>

#include <iostream>
#include <string>

#include "HAL/Platform.h"
#include "Macros.h"
#include "Math/Math.h"

