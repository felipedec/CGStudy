#pragma once

#include "CoreTypes.h"
#include "Math/Plane.h"
#include "Math/Matrix.h"

class FScaleMatrix  : public FMatrix
{
public:

	FORCEINLINE FScaleMatrix(float Scale) : FMatrix(
		FPlane(Scale, 0.0f, 0.0f, 0.0f),
		FPlane(0.0f, Scale, 0.0f, 0.0f),
		FPlane(0.0f, 0.0f, Scale, 0.0f),
		FPlane(0.0f, 0.0f, 0.0f, 1.0f)
	)
	{ }

	FORCEINLINE FScaleMatrix(const FVector& Scale) : FMatrix(
		FPlane(Scale.X, 0.0f, 0.0f, 0.0f),
		FPlane(0.0f, Scale.Y, 0.0f, 0.0f),
		FPlane(0.0f, 0.0f, Scale.Z, 0.0f),
		FPlane(0.0f, 0.0f, 0.0f, 1.0f)
	)
	{ }

public:

	/** Fábrica de matriz */
	static FMatrix Make(float Scale)
	{
		return FScaleMatrix(Scale);
	}

	/** Fábrica de matriz */
	static FMatrix Make(const FVector& Scale)
	{
		return FScaleMatrix(Scale);
	}
};