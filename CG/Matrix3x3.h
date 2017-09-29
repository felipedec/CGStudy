// Este código pertence a um projeto pessoal,
// baseado no código aberto da Unreal Engine,
// com o intuito de aprendizado. Apenas as 
// estrutura básica das classes são semelhantes
// e as vezes iguais, já os corpos de métodos
// são implementações próprias do desenvolvedor
// deste projeto.
//
// Saiba mais:
// https://github.com/felipedec/CGStudy

#pragma once

#include "Core.h"
#include "Vector3.h"

struct FMatrix3x3
{
public:

	union
	{
		struct
		{
			/** Componentes da primeira linha */
			float M00, M01, M02;

			/** Componentes da segunda linha */
			float M10, M11, M12;

			/** Componentes da terceira linha */
			float M20, M21, M22;
		};

		struct
		{
			float Components[3][3];
		};
	};

public:

	/** Matríz identidade */
	static FMatrix3x3 Identy;

public:

	/** Construtor sem inicialização dos componentes */
	FORCEINLINE FMatrix3x3() = default;

	/** Construtor passando cada linha como vetores */
	FORCEINLINE FMatrix3x3(const FVector3& X, const FVector3& Y, const FVector3& Z);

	/** Construtor passando cada componente */
	FORCEINLINE FMatrix3x3(const float InM00, const float InM01, const float InM02,
								  const float InM10, const float InM11, const float InM12,
								  const float InM20, const float InM21, const float InM22);

public:

	/**
	 * Obtem o resultado da multiplicação dessa matríz com outra.
	 *
	 * @param Other Outra matríz da operação.
	 * @return Resultado da multiplicação entre as matrízes.
	 */
	FORCEINLINE FMatrix3x3 operator*(const FMatrix3x3& Other) const;

	/**
	 * Obtem o resultado da multiplicação dessa matríz com uma escalar.
	 *
	 * @param Scale Escalar.
	 * @return Resultado da multiplicação da matríz pela escalar.
	 */
	FORCEINLINE FMatrix3x3 operator*(const float Scale) const;

	/**
	 * Obtem o resultado da divisão dessa matríz com uma escalar.
	 *
	 * @param Scale Escalar.
	 * @return Resultado da divisão da matríz pela escalar.
	 */
	FORCEINLINE FMatrix3x3 operator/(const float Scale) const;

	/**
	 * Obtem uma matríz sendo cada componente a soma dos respectivos componentes desta matríz e a outra.
	 *
	 * @param Other Outra matríz.
	 * @return Matríz com a soma dos componentes.
	 */
	FORCEINLINE FMatrix3x3 operator+(const FMatrix3x3& Other) const;

	/**
	 * Obtem uma matríz sendo cada componente a subtração dos respectivos componentes desta matríz e a outra.
	 *
	 * @param Other Outra matríz.
	 * @return Matríz com a subtração dos componentes.
	 */
	FORCEINLINE FMatrix3x3 operator-(const FMatrix3x3& Other) const;

	/**
	 * Obtem o resultado do produto da matríz com um vetor de 3 componentes.
	 *
	 * @param V Vetor.
	 * @return O resultado do produto da matríz com um vetor.
	 */
	FORCEINLINE FVector3 operator*(const FVector3& V) const;

public:

	/** Obtém uma cópia desta matríz transposta */
	FORCEINLINE FMatrix3x3 GetTranspose() const;
};

/* ---------------- Inline functions ---------------- */

FORCEINLINE FMatrix3x3::FMatrix3x3(const FVector3& X, const FVector3& Y, const FVector3& Z)
{
	M00 = X.X; M01 = X.Y; M02 = X.Z;
	M10 = Y.X; M11 = Y.Y; M12 = Y.Z;
	M20 = Z.X; M21 = Z.Y; M22 = Z.Z;
}

FORCEINLINE FMatrix3x3::FMatrix3x3(const float InM00, const float InM01, const float InM02,
											  const float InM10, const float InM11, const float InM12,
											  const float InM20, const float InM21, const float InM22)
{
	M00 = InM00; M01 = InM01; M02 = InM02;
	M10 = InM10; M11 = InM11; M12 = InM12;
	M20 = InM20; M21 = InM21; M22 = InM22;
}

FORCEINLINE FMatrix3x3 FMatrix3x3::operator*(const FMatrix3x3& Other) const
{
	return FMatrix3x3
	(
		M00 * Other.M00 + M01 * Other.M10 + M02 * Other.M20,
		M00 * Other.M01 + M01 * Other.M11 + M02 * Other.M21,
		M00 * Other.M02 + M01 * Other.M12 + M02 * Other.M22,
		M10 * Other.M00 + M11 * Other.M10 + M12 * Other.M20,
		M10 * Other.M01 + M11 * Other.M11 + M12 * Other.M21,
		M10 * Other.M02 + M11 * Other.M12 + M12 * Other.M22,
		M20 * Other.M00 + M21 * Other.M10 + M22 * Other.M20,
		M20 * Other.M01 + M21 * Other.M11 + M22 * Other.M21,
		M20 * Other.M02 + M21 * Other.M12 + M22 * Other.M22
	);
}

FORCEINLINE FMatrix3x3 FMatrix3x3::operator+(const FMatrix3x3& Other) const
{
	return FMatrix3x3
	(
		Other.M00 + M00, Other.M01 + M01, Other.M02 + M02,
		Other.M10 + M10, Other.M11 + M11, Other.M12 + M12,
		Other.M20 + M20, Other.M21 + M21, Other.M22 + M22
	);
}

FORCEINLINE FMatrix3x3 FMatrix3x3::operator-(const FMatrix3x3& Other) const
{
	return FMatrix3x3
	(
		M00 - Other.M00, M01 - Other.M01, M02 - Other.M02,
		M10 - Other.M10, M11 - Other.M11, M12 - Other.M12,
		M20 - Other.M20, M21 - Other.M21, M22 - Other.M22
	);
}

FORCEINLINE FMatrix3x3 FMatrix3x3::operator*(const float Scale) const
{
	return FMatrix3x3
	(
		M00 * Scale, M01 * Scale, M02 * Scale,
		M10 * Scale, M11 * Scale, M12 * Scale,
		M20 * Scale, M21 * Scale, M22 * Scale
	);
}

FORCEINLINE FMatrix3x3 FMatrix3x3::operator/(const float Scale) const
{
	return FMatrix3x3
	(
		M00 / Scale, M01 / Scale, M02 / Scale,
		M10 / Scale, M11 / Scale, M12 / Scale,
		M20 / Scale, M21 / Scale, M22 / Scale
	);
}

FORCEINLINE FVector3 FMatrix3x3::operator*(const FVector3& V) const
{
	return FVector3
	(
		M00 * V.X + M01 * V.Y + M02 * V.Z,
		M10 * V.X + M11 * V.Y + M12 * V.Z,
		M20 * V.X + M21 * V.Y + M22 * V.Z
	);
}

FORCEINLINE FMatrix3x3 FMatrix3x3::GetTranspose() const
{
	return FMatrix3x3(M00, M10, M20, M01, M11, M21, M02, M12, M22);
}