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

#include "CoreTypes.h"

struct FVertex
{
public:

	FVector Position;
	FVector Normal;
	FVector2 TexCoord0;
	FColor32 Color;

public:

	FVertex(const FVector& InPosition, const FVector& InNormal, const FVector2& InTexCoord0, const FColor32& InColor) :
		Position(InPosition),
		Normal(InNormal),
		TexCoord0(InTexCoord0),
		Color(InColor)
	{}
};