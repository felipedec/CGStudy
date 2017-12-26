/*----------------------------------------------------------------------------
         Código baseado no código aberto da Unreal Engine
----------------------------------------------------------------------------*/

#pragma once

/*----------------------------------------------------------------------------
			PlatformTypes.
----------------------------------------------------------------------------*/

#if defined(PLATFORM_WINDOWS)
	#include "Windows/WindowsPlatform.h"
#else
	#error Nenhuma plataforma definida.
#endif

/*----------------------------------------------------------------------------
			Definição dos tipos.
----------------------------------------------------------------------------*/

// Tipos Inteiros com Sinal
typedef FPlatformTypes::uint8 uint8;
typedef FPlatformTypes::uint16 uint16;
typedef FPlatformTypes::uint32 uint32;
typedef FPlatformTypes::uint64 uint64;

// Tipos Interios sem Sinal
typedef FPlatformTypes::int8 int8; 
typedef FPlatformTypes::int16 int16;
typedef FPlatformTypes::int32 int32;
typedef FPlatformTypes::int64 int64;

// Tipos de Caracteres
typedef FPlatformTypes::ANSICHAR ANSICHAR;
typedef FPlatformTypes::WIDECHAR WIDECHAR;
typedef FPlatformTypes::CHAR8 CHAR8;
typedef FPlatformTypes::CHAR16 CHAR16;
typedef FPlatformTypes::CHAR32 CHAR32;
typedef FPlatformTypes::TCHAR TCHAR;

// Tipos Inteiros de mesmo tamanho de um ponteiro
typedef FPlatformTypes::UPTRINT UPTRINT;
typedef FPlatformTypes::PTRINT PTRINT;

// Tipo inteiro capaz de respresentar o tamanho de qualquer objeto em bytes.
typedef FPlatformTypes::SIZE_T SIZE_T;

// SIZE_T com sinal
typedef FPlatformTypes::SSIZE_T SSIZE_T;

// Autoexplicativo.
typedef FPlatformTypes::TYPE_OF_NULL TYPE_OF_NULL;
typedef FPlatformTypes::TYPE_OF_NULLPTR TYPE_OF_NULLPTR;

/*----------------------------------------------------------------------------
			Testar os tipos da plataforma.
----------------------------------------------------------------------------*/

#include "Templates/TypeTraits.h"

// Mesmos testes feitos na Unreal (Runtime/Core/Public/HAL/Platform.h).
namespace Engine_StaticAssertation
{
	static_assert(PLATFORM_32BITS || PLATFORM_64BITS, "Type tests pointer size failed.");
	static_assert(PLATFORM_32BITS != PLATFORM_64BITS, "Type tests pointer exclusive failed.");
	static_assert(!PLATFORM_64BITS || sizeof(void*) == 8, "Pointer size is 64bit, but pointers are short.");
	static_assert(PLATFORM_64BITS || sizeof(void*) == 4, "Pointer size is 32bit, but pointers are long.");

	static_assert(char(-1) < char(0), "Unsigned char type test failed.");

	static_assert(!IsSame<ANSICHAR, WIDECHAR>, "ANSICHAR and WIDECHAR should be different types.");
	static_assert(!IsSame<ANSICHAR, CHAR16>, "ANSICHAR and CHAR16 should be different types.");
	static_assert(!IsSame<WIDECHAR, CHAR16>, "WIDECHAR and CHAR16 should be different types.");
	static_assert(IsSame<TCHAR, ANSICHAR> || IsSame<TCHAR, WIDECHAR>, "TCHAR should either be ANSICHAR or WIDECHAR.");

	static_assert(sizeof(uint8) == 1, "uint8 type size test failed.");
	static_assert(sizeof(uint16) == 2, "uint16 type size test failed.");
	static_assert(sizeof(uint32) == 4, "uint32 type size test failed.");
	static_assert(sizeof(uint64) == 8, "uint64 type size test failed.");

	static_assert(sizeof(int8) == 1, "int8 type size test failed.");
	static_assert(sizeof(int16) == 2, "int16 type size test failed.");
	static_assert(sizeof(int32) == 4, "int32 type size test failed.");
	static_assert(sizeof(int64) == 8, "int64 type size test failed.");

	static_assert(sizeof(PTRINT) == sizeof(void *), "PTRINT type size test failed.");
	static_assert(sizeof(UPTRINT) == sizeof(void *), "UPTRINT type size test failed.");
	static_assert(sizeof(SIZE_T) == sizeof(void *), "SIZE_T type size test failed.");

	static_assert(sizeof(ANSICHAR) == 1, "ANSICHAR type size test failed.");
	static_assert(sizeof(WIDECHAR) == 2 || sizeof(WIDECHAR) == 4, "WIDECHAR type size test failed.");
	static_assert(sizeof(CHAR16) == 2, "CHAR16 type size test failed.");

	static_assert(int32(uint8(-1)) == 0xFF, "uint8 type sign test failed.");
	static_assert(int32(uint16(-1)) == 0xFFFF, "uint16 type sign test failed.");
	static_assert(int64(uint32(-1)) == int64(0xFFFFFFFF), "uint32 type sign test failed.");
	static_assert(uint64(-1) > uint64(0), "uint64 type sign test failed.");

	static_assert(int32(int8(-1)) == -1, "int8 type sign test failed.");
	static_assert(int32(int16(-1)) == -1, "int16 type sign test failed.");
	static_assert(int64(int32(-1)) == int64(-1), "int32 type sign test failed.");
	static_assert(int64(-1) < int64(0), "int64 type sign test failed.");

	static_assert(PTRINT(-1) < PTRINT(0), "PTRINT type sign test failed.");
	static_assert(UPTRINT(-1) > UPTRINT(0), "UPTRINT type sign test failed.");
	static_assert(SIZE_T(-1) > SIZE_T(0), "SIZE_T type sign test failed.");
}

/*----------------------------------------------------------------------------
			Plataformas.
----------------------------------------------------------------------------*/

#if defined(PLATFORM_WINDOWS)
	#include "Windows/WindowsPlatformConsoleWindow.h"
	#include "Windows/WindowsPlatformTime.h"
#endif

/*----------------------------------------------------------------------------
			Macros.
----------------------------------------------------------------------------*/

#if !defined(TEXT)
	#define TEXT(Txt) (L##Txt)
#endif // TEXT

#if _DEBUG && PLATFORM_HAS_NATIVE_CONSOLE
	#define LE_DebugLog(...) FConsoleWindow::Printf(__VA_ARGS__)
#else
	#define LE_DebugLog(...)
#endif 
