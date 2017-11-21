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