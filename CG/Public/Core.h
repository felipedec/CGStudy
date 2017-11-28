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
			Core.
----------------------------------------------------------------------------*/

#define CORE_API

/*----------------------------------------------------------------------------
			OpenGL.

			TODO: Colocar em um arquivo separado.
----------------------------------------------------------------------------*/

#define GLEW_STATIC 
#pragma comment(lib, "opengl32.lib")
#pragma comment(lib, "glu32.lib")
#pragma comment(lib, "glew32s.lib")

#include <gl/glew.h>
#include "../ThirdParty/SOIL/SOIL.h"

/*----------------------------------------------------------------------------
			Arquivos std.

			TODO: Substituir.
----------------------------------------------------------------------------*/

#include <iostream>
#include <string>

/*----------------------------------------------------------------------------
			Includes.
----------------------------------------------------------------------------*/

#include "HAL/Platform.h"
#include "Template/TypeTraits.h"
#include "Macros.h"
#include "Math/Math.h"

