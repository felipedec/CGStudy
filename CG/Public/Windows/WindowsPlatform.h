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

#include "GenericPlatform/GenericPlatform.h"

struct FWindowsPlatformTypes;
typedef FWindowsPlatformTypes FPlatformTypes;

/*----------------------------------------------------------------------------
			Platform API Headers.
----------------------------------------------------------------------------*/

#include <windows.h>
#include <winbase.h>

/*----------------------------------------------------------------------------
			PlatformTypes.
----------------------------------------------------------------------------*/

struct FWindowsPlatformTypes : public FGenericPlatformTypes
{
#ifdef _WIN64
	typedef unsigned __int64 SIZE_T;
	typedef __int64 SSIZE_T;
#else
	typedef unsigned long SIZE_T;
	typedef long SSIZE_T;
#endif
};

/*----------------------------------------------------------------------------
			Macros.
----------------------------------------------------------------------------*/

#define FORCEINLINE __forceinline
#define ABSTRACT abstract

#if defined(__clang__) || _MSC_VER >= 1900
	#define CONSTEXPR constexpr
#else
	#define CONSTEXPR
#endif 

#define DLLIMPORT __declspec(dllimport)
#define DLLEXPORT __declspec(dllexpsort)

#define LINE_TERMINATOR TEXT("\r\n")
#define LINE_TERMINATOR_ANSI "\r\n"

#define USE_DIRECTX_MATH 1

#define PLATFORM_HAS_NATIVE_CONSOLE 1
#define PLATFORM_DESKTOP 1
#define PLATFORM_64BITS	_WIN64

#if defined(__GNUC__)
	#define GCC_ALIGN(n) __attribute__((aligned(n)))
	#define MS_ALIGN(n)
#else
	#define GCC_ALIGN(n)
	#define MS_ALIGN(n) __declspec(align(n)) 
#endif

