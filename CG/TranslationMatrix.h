/*----------------------------------------------------------------------------
			Este c�digo pertence a um projeto pessoal,
			baseado no c�digo aberto da Unreal Engine,
			com o intuito de aprendizado. Apenas as
			estrutura b�sica das classes s�o semelhantes
			e as vezes iguais, j� os corpos de m�todos
			s�o implementa��es pr�prias do desenvolvedor
			deste projeto.
			
			Saiba mais:
			https://github.com/felipedec/CGStudy
----------------------------------------------------------------------------*/

#pragma once

#include "CoreTypes.h"


struct FTranslationMatrix : public FMatrix
{
public:
	/** Constr�i a matr�z basedo em um vetor passado */
	FORCEINLINE FTranslationMatrix(const FVector& Delta)
	: FMatrix
	(
		FVector4(1.0f, 0.0f, 0.0f, 0.0f),
		FVector4(0.0f, 1.0f, 0.0f, 0.0f),
		FVector4(0.0f, 0.0f, 1.0f, 0.0f),
		FVector4(Delta.X, Delta.Y, Delta.Z, 1.0f)
	) { }

public:

	/** F�brica de matr�zes */
	static CORE_API FMatrix Make(const FVector& Delta)
	{
		return FTranslationMatrix(Delta);
	}
};
