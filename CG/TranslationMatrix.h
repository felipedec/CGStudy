/*----------------------------------------------------------------------------
			Este código pertence a um projeto pessoal,
			baseado no código aberto da Unreal Engine,
			com o intuito de aprendizado. Apenas as
			estrutura básica das classes são semelhantes
			e as vezes iguais, já os corpos de métodos
			são implementações próprias do desenvolvedor
			deste projeto.
			
			Saiba mais:
			https://github.com/felipedec/CGStudy
----------------------------------------------------------------------------*/

#pragma once

#include "CoreTypes.h"


struct FTranslationMatrix : public FMatrix
{
public:
	/** Constrói a matríz basedo em um vetor passado */
	FORCEINLINE FTranslationMatrix(const FVector& Delta)
	: FMatrix
	(
		FVector4(1.0f, 0.0f, 0.0f, 0.0f),
		FVector4(0.0f, 1.0f, 0.0f, 0.0f),
		FVector4(0.0f, 0.0f, 1.0f, 0.0f),
		FVector4(Delta.X, Delta.Y, Delta.Z, 1.0f)
	) { }

public:

	/** Fábrica de matrízes */
	static CORE_API FMatrix Make(const FVector& Delta)
	{
		return FTranslationMatrix(Delta);
	}
};
