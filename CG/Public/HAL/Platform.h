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

/*----------------------------------------------------------------------------
			PlatformTypes.
----------------------------------------------------------------------------*/

#if defined(PLATFORM_WINDOWS)
	#include "Windows/Windows.h"
	typedef FWindowsPlatformTypes FPlatformTypes;
#else
	#error Platform is not defined.
#endif

/*----------------------------------------------------------------------------
			Definição dos tipos.
----------------------------------------------------------------------------*/

typedef FPlatformTypes::uint8 uint8;
typedef FPlatformTypes::uint16 uint16;
typedef FPlatformTypes::uint32 uint32;
typedef FPlatformTypes::uint64 uint64;

typedef FPlatformTypes::int8 int8; 
typedef FPlatformTypes::int16 int16;
typedef FPlatformTypes::int32 int32;
typedef FPlatformTypes::int64 int64;

typedef FPlatformTypes::ANSICHAR ANSICHAR;
typedef FPlatformTypes::WIDECHAR WIDECHAR;
typedef FPlatformTypes::CHAR8 CHAR8;
typedef FPlatformTypes::CHAR16 CHAR16;
typedef FPlatformTypes::CHAR32 CHAR32;
typedef FPlatformTypes::TCHAR TCHAR;

typedef FPlatformTypes::UPTRINT UPTRINT;
typedef FPlatformTypes::PTRINT PTRINT;

typedef FPlatformTypes::SIZE_T SIZE_T;
typedef FPlatformTypes::SSIZE_T SSIZE_T;
typedef FPlatformTypes::TYPE_OF_NULL TYPE_OF_NULL;
typedef FPlatformTypes::TYPE_OF_NULLPTR TYPE_OF_NULLPTR;

/*----------------------------------------------------------------------------
			Para disponiblizar os TypeTraits para os documentos
			que tratam da parta de plataforma incluímos ele aqui,
			logo apóis a definição dos tipos da plataforma, já
			que ele necessita delas.
----------------------------------------------------------------------------*/

#include "Template/TypeTraits.h"

/*----------------------------------------------------------------------------
			Plataformas.
----------------------------------------------------------------------------*/

#if defined(PLATFORM_WINDOWS)
	// FNativeConsole
	#define PLATFORM_HAS_NATIVE_CONSOLE
	#include "Windows/WindowsNativeConsole.h"
	typedef FWindowsNativeConsole FNativeConsole;
#else
	// FNativeConsole
	#include "GenericPlatform/GenericPlatformNativeConsole.h"
	typedef FGenericPlatformNativeConsole FNativeConsole;
#endif

/*----------------------------------------------------------------------------
			Macros.
----------------------------------------------------------------------------*/

#if !defined(TEXT)
	#define TEXT(Txt) (L##Txt)
#endif // TEXT

#if defined(_DEBUG) && defined(PLATFORM_HAS_NATIVE_CONSOLE)
	#define LE_DebugLog_INNER(Color, ...) \
		FNativeConsole::Printf( \
		PREPROCESSOR_TO_STRING(__FILE__) \
		" (line:" \
		PREPROCESSOR_TO_STRING(__LINE__) \
		"): " \
		__VA_ARGS__) \

	#define LE_DebugLog(...) LE_DebugLog_INNER(ENativeConsoleTextColor::Neutral, __VA_ARGS__)
	#define LE_DebugLogWarning(...) LE_DebugLog_INNER(ENativeConsoleTextColor::Warning, __VA_ARGS__)
	#define LE_DebugLogError(...) LE_DebugLog_INNER(ENativeConsoleTextColor::Error, __VA_ARGS__)
	#define LE_DebugLogSuccess(...) LE_DebugLog_INNER(ENativeConsoleTextColor::Success, __VA_ARGS__)
#else
	#define LE_DebugLog(...)
	#define LE_DebugLogWarning(...)
	#define LE_DebugLogError(...)
	#define LE_DebugLogSuccess(...)
#endif 

