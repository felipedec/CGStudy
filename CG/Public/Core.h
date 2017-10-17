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

/*----------------------------------------------------------------------------
			Platform Macros.
----------------------------------------------------------------------------*/

#define USE_DIRECTX_MATH 1

/*----------------------------------------------------------------------------
			Includes.
----------------------------------------------------------------------------*/

#include <iostream>
#include <string>

#include "Macros.h"
#include "Platform/GenericPlataform.h"
#include "Math/Math.h"
#include "Template/TypeTraits.h"
#include "Math/BezierUtil.h"
#include "LinkedList.h"