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

#include "HAL/Platform.h"

template <int32 Size, uint32 Alignment> struct TAlignedBytes;

template <int32 Size>
struct TAlignedBytes<Size, 1>
{
	uint8 Pad[Size];
};

#define IMPLEMENT_ALIGNED_STORAGE(Align) \
	template<int32 Size> \
	struct TAlignedBytes<Size, Align> \
	{ \
		struct MS_ALIGN(Align) TPadding \
		{ \
			uint8 Pad[Size]; \
		} GCC_ALIGN(Align); \
		TPadding Padding; \
	}; \

IMPLEMENT_ALIGNED_STORAGE(16);
IMPLEMENT_ALIGNED_STORAGE(8);
IMPLEMENT_ALIGNED_STORAGE(4);
IMPLEMENT_ALIGNED_STORAGE(2);