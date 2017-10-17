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