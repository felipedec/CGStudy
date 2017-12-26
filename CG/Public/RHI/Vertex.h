/*----------------------------------------------------------------------------
Código baseado no código aberto da Unreal Engine
----------------------------------------------------------------------------*/

#include "CoreTypes.h"

struct FVertex
{
public:

	FVector Position;
	FVector Normal;
	FVector2 TexCoord0;
	FColor32 Color;

public:

	FORCEINLINE FVertex(const FVector& InPosition, const FVector& InNormal, const FVector2& InTexCoord0, const FColor32& InColor) :
		Position(InPosition),
		Normal(InNormal),
		TexCoord0(InTexCoord0),
		Color(InColor)
	{}

	FORCEINLINE FVertex() :
		Color(FColor32::White)
	{}
};