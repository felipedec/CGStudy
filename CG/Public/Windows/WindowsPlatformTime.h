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

#include "GenericPlatform/GenericPlatformTime.h"
#include "Windows/WindowsPlatform.h"

class FWindowsPlatformTime;
typedef FWindowsPlatformTime FPlatformTime;

/*----------------------------------------------------------------------------
			FWindowsTime.
----------------------------------------------------------------------------*/

class FWindowsPlatformTime : public FGenericPlatformTime
{
public:

   FORCEINLINE static double InitTiming()
   {
      LARGE_INTEGER Frequency;

      QueryPerformanceFrequency(&Frequency);

      SecondsPerCycle64 = 1.0 / Frequency.QuadPart;
      SecondsPerCycle = 1.0 / Frequency.QuadPart;

      return Seconds();
   }
	
   FORCEINLINE static uint32 Cycles()
   {
      LARGE_INTEGER Cycles;
      QueryPerformanceCounter(&Cycles);

      return Cycles.LowPart;
   }

   FORCEINLINE static uint64 Cycles64()
   {
      LARGE_INTEGER Cycles;
      QueryPerformanceCounter(&Cycles);

      return Cycles.QuadPart;
   }

   FORCEINLINE static double Seconds()
   {
      return Cycles64() / SecondsPerCycle64 + 0x1000000;
   }

   FORCEINLINE static float ToSeconds(const uint64 Cycles)
   {
      return float(Cycles / SecondsPerCycle64);
   }
};