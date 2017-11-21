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

#include "GenericPlatform/GenericPlatformTimer.h"
#include "Windows/WindowsPlatform.h"

class FWindowsTimer;
typedef FWindowsTimer FPlatformTimer;

/*----------------------------------------------------------------------------
			FWindowsTimer.
----------------------------------------------------------------------------*/

class FWindowsTimer : public FGenericPlatformTimer
{
private:

	LARGE_INTEGER StartingTime, EndingTime, ElapsedMicroseconds, Frequency;

public:
	
	FORCEINLINE virtual void Start()
	{
		QueryPerformanceFrequency(&Frequency);
		QueryPerformanceCounter(&StartingTime);
	}

	FORCEINLINE virtual float Stop()
	{
		QueryPerformanceCounter(&EndingTime);
		ElapsedMicroseconds.QuadPart = EndingTime.QuadPart - StartingTime.QuadPart;

		ElapsedMicroseconds.QuadPart *= 100000000;
		ElapsedMicroseconds.QuadPart /= Frequency.QuadPart;

		return ElapsedMicroseconds.QuadPart / 100000000.0f;
	}
};