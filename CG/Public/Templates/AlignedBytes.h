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