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

#include "CoreTypes.h"


class FTranslationMatrix : public FMatrix
{
public:

	FORCEINLINE FTranslationMatrix(const FVector& Delta)
		: FTranslationMatrix(Delta.X, Delta.Y, Delta.Z)
	{

	}

	FORCEINLINE FTranslationMatrix(const float X, const float Y, const float Z)
		: FMatrix
	(
		FVector4(1.0f, 0.0f, 0.0f, 0.0f),
		FVector4(0.0f, 1.0f, 0.0f, 0.0f),
		FVector4(0.0f, 0.0f, 1.0f, 0.0f),
		FVector4(X, Y, Z, 1.0f)
	) { }

public:

	/** Fábrica de matrízes */
	static CORE_API FMatrix Make(const FVector& Delta)
	{
		return FTranslationMatrix(Delta);
	}

	/** Fábrica de matrízes */
	static CORE_API FMatrix Make(const float X, const float Y, const float Z)
	{
		return FTranslationMatrix(X, Y, Z);
	}
};
  