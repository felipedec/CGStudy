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
			Headers.
----------------------------------------------------------------------------*/

#include <windows.h>

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


struct FWindowsUtility
{
public:

	FORCEINLINE static LPWSTR GetFormattedMessageW(LPWSTR Format, ...)
	{
		LPWSTR BufferPtr = NULL;
		const DWORD Flags = FORMAT_MESSAGE_FROM_STRING | FORMAT_MESSAGE_ALLOCATE_BUFFER;

		va_list Args = NULL;
		va_start(Args, Format);

		FormatMessageW(Flags, Format, 0, 0, (LPWSTR)&BufferPtr, 0, &Args);

		va_end(Args);

		return BufferPtr;
	}

	FORCEINLINE static LPSTR GetFormattedMessageA(LPSTR Format, ...)
	{
		LPSTR BufferPtr = NULL;
		const DWORD Flags = FORMAT_MESSAGE_FROM_STRING | FORMAT_MESSAGE_ALLOCATE_BUFFER;

		va_list Args = NULL;
		va_start(Args, Format);

		FormatMessageA(Flags, Format, 0, 0,(LPSTR)&BufferPtr, 0, &Args);
		va_end(Args);

		return BufferPtr;
	}
};