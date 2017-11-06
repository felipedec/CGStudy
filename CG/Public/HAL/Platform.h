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
			FNativeConsole.
----------------------------------------------------------------------------*/

#if defined(PLATFORM_WINDOWS)
	#define PLATFORM_HAS_NATIVE_CONSOLE
	#include "Windows/WindowsNativeConsole.h"
	typedef FWindowsNativeConsole FNativeConsole;
#endif

/*----------------------------------------------------------------------------
			Macros.
----------------------------------------------------------------------------*/

#if !defined(TEXT)
	#define TEXT(Txt) (L##Txt)
#endif // TEXT

#if defined(_DEBUG) && defined(PLATFORM_HAS_NATIVE_CONSOLE)
	#define LE_Log(...) FNativeConsole::Printf(ENativeConsoleTextColor::Neutral, __VA_ARGS__)
	#define LE_LogWarning(...) FNativeConsole::Printf(ENativeConsoleTextColor::Warning, __VA_ARGS__)
	#define LE_LogError(...) FNativeConsole::Printf(ENativeConsoleTextColor::Error, __VA_ARGS__)
	#define LE_LogSuccess(...) FNativeConsole::Printf(ENativeConsoleTextColor::Success, __VA_ARGS__)
#else
	#define LE_Log(...)
	#define LE_LogWarning(...)
	#define LE_LogError(...)
	#define LE_LogSuccess(...)
#endif 

