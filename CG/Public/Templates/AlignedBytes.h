// Código baseado no código aberto da Unreal Engine

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
		struct MS_ALIGN(Align) FPadding \
		{ \
			uint8 Pad[Size]; \
		} GCC_ALIGN(Align); \
		FPadding Padding; \
	}; \

IMPLEMENT_ALIGNED_STORAGE(16);
IMPLEMENT_ALIGNED_STORAGE(8);
IMPLEMENT_ALIGNED_STORAGE(4);
IMPLEMENT_ALIGNED_STORAGE(2);