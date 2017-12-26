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

#include "Core.h"

#if PLATFORM_HAS_BSD_TIME
   #include <sys/time.h>
#endif // PLATFORM_HAS_BSD_TIME

struct CORE_API FGenericPlatformTime
{
protected:

   static double SecondsPerCycle;
   static double SecondsPerCycle64;

public:

#if PLATFORM_HAS_BSD_TIME 

   FORCEINLINE static double InitTiming()
   {
      SecondsPerCycle = 1.0f / 1000000.0f;
      SecondsPerCycle64 = 1.0 / 1000000.0;

      return FPlatformTime::Seconds();
   }

   FORCEINLINE static double Seconds()
   {
      struct timeval tv;
      gettimeofday(&tv, NULL);
      return ((double)tv.tv_sec) + (((double)tv.tv_usec) / 1000000.0);
   }

   FORCEINLINE static uint32 Cycles()
   {
      struct timeval tv;
      gettimeofday(&tv, NULL);
      return (uint32)((((uint64)tv.tv_sec) * 1000000ULL) + (((uint64)tv.tv_usec)));
   }

   FORCEINLINE static uint64 Cycles64()
   {
      struct timeval tv;
      gettimeofday(&tv, NULL);
      return ((((uint64)tv.tv_sec) * 1000000ULL) + (((uint64)tv.tv_usec)));
   }

#endif // PLATFORM_HAS_BSD_TIME

   FORCEINLINE static double GetSecondsPerCycle()
   {
      return SecondsPerCycle;
   }

   FORCEINLINE static float ToMilliseconds(const uint32 Cycles)
   {
      return (float)double(SecondsPerCycle * 1000.0 * Cycles);
   }

   FORCEINLINE static float ToSeconds(const uint32 Cycles)
   {
      return (float)double(SecondsPerCycle * Cycles);
   }

   FORCEINLINE static double GetSecondsPerCycle64()
   {
      // check(SecondsPerCycle64 != 0.0);
      return SecondsPerCycle64;
   }

   FORCEINLINE static double ToMilliseconds64(const uint64 Cycles)
   {
      return ToSeconds64(Cycles) * 1000.0;
   }

   FORCEINLINE static double ToSeconds64(const uint64 Cycles)
   {
      return GetSecondsPerCycle64() * double(Cycles);
   }
};
