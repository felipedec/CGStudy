// Código baseado no código aberto da Unreal Engine

#pragma once

#include "CoreTypes.h"
#include "Math/Plane.h"
#include "Math/Matrix.h"

#define Z_PRECISION 0.0f

#ifdef _MSC_VER
#pragma warning(push)
// Desabilitar mensagem de possível divisão por zero.
#pragma warning(disable:4723)
#endif

class FPerspectiveMatrix : public FMatrix
{
public:

	FORCEINLINE FPerspectiveMatrix(float HalfFOV, float Width, float Height, float MinZ, float MaxZ) 
      : FMatrix(
         FPlane(1.0f / FMath::Tan(HalfFOV), 0.0f, 0.0f, 0.0f),
         FPlane(0.0f, Width / FMath::Tan(HalfFOV) / Height, 0.0f, 0.0f),
         FPlane(0.0f, 0.0f, ((MinZ == MaxZ) ? (1.0f - Z_PRECISION) : MaxZ / (MaxZ - MinZ)), 1.0f),
         FPlane(0.0f, 0.0f, -MinZ * ((MinZ == MaxZ) ? (1.0f - Z_PRECISION) : MaxZ / (MaxZ - MinZ)), 0.0f)
      )
   { }

};

#ifdef _MSC_VER
#pragma warning(pop)
#endif