/*----------------------------------------------------------------------------
         Código baseado no código aberto da Unreal Engine
----------------------------------------------------------------------------*/
#pragma once

#include "Core.h"

/*----------------------------------------------------------------------------
			FGenericPlatformConsoleWindow.
----------------------------------------------------------------------------*/

class FGenericPlatformConsoleWindow
{
public:

	template <typename ...TArgs>
	FORCEINLINE static void Printf(const TCHAR* Format, const TArgs&... Args) {};

	template <typename ...TArgs>
	FORCEINLINE static void Printf(const CHAR* Format, const TArgs&... Args) {};

	FORCEINLINE static void Close() {};
};
