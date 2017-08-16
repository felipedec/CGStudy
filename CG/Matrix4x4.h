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
#include "Vector4.h"

struct FMatrix4x4
{
public:

	/** Componentes da primeira linha */
	float M00, M01, M02, M03;

	/** Componentes da segunda linha */
	float M10, M11, M12, M13;

	/** Componentes da terceira linha */
	float M20, M21, M22, M23;

	/** Componentes da quarta linha */
	float M30, M31, M32, M33;

public:

	/** Matríz identidade */
	static FMatrix4x4 Identy;

public:

	/** Construtor sem inicialização dos componentes */
	FORCEINLINE FMatrix4x4() = default;

	/** Construtor passando cada linha como vetores */
	FORCEINLINE FMatrix4x4(const FVector4& X, const FVector4& Y, const FVector4& Z, const FVector4& W);

	/** Construtor passando cada componente */
	FORCEINLINE FMatrix4x4(const float InM00, const float InM01, const float InM02, const float InM03,
								  const float InM10, const float InM11, const float InM12, const float InM13,
								  const float InM20, const float InM21, const float InM22, const float InM23,
								  const float InM30, const float InM31, const float InM32, const float InM33);

public:

	/**
	 *
	 * Obtem o resultado da multiplicação dessa matríz com outra.
	 *
	 * @param Other Outra matríz da operação.
	 * @return Resultado da multiplicação entre as matrízes.
	 */
	FORCEINLINE FMatrix4x4 operator*(const FMatrix4x4& Other) const;

	/**
	 *
	 * Obtem o resultado da multiplicação dessa matríz com uma escalar.
	 *
	 * @param Scale Escalar.
	 * @return Resultado da multiplicação da matríz pela escalar.
	 */
	FORCEINLINE FMatrix4x4 operator*(const float Scale) const;

	/**
	 *
	 * Obtem o resultado da divisão dessa matríz com uma escalar.
	 *
	 * @param Scale Escalar.
	 * @return Resultado da divisão da matríz pela escalar.
	 */
	FORCEINLINE FMatrix4x4 operator/(const float Scale) const;

	/**
	 *
	 * Obtem uma matríz sendo cada componente a soma dos respectivos componentes desta matríz e a outra.
	 *
	 * @param Other Outra matríz.
	 * @return Matríz com a soma dos componentes.
	 */
	FORCEINLINE FMatrix4x4 operator+(const FMatrix4x4& Other) const;

	/**
	 *
	 * Obtem uma matríz sendo cada componente a subtração dos respectivos componentes desta matríz e a outra.
	 *
	 * @param Other Outra matríz.
	 * @return Matríz com a subtração dos componentes.
	 */
	FORCEINLINE FMatrix4x4 operator-(const FMatrix4x4& Other) const;

	/**
	 *
	 * Obtem o resultado do produto da matríz com um vetor de 4 componentes.
	 *
	 * @param V Vetor.
	 * @return O resultado do produto da matríz com um vetor.
	 */
	FORCEINLINE FVector4 operator*(const FVector4& V) const;

public:

	/** Obtém uma cópia desta matríz transposta */
	FORCEINLINE FMatrix4x4 GetTranspose() const;

	/** Copiar os componente em um vetor */
	FORCEINLINE void CopyTo(float** Buffer) const;
};

/* ---------------- Inline functions ---------------- */

FORCEINLINE FMatrix4x4::FMatrix4x4(const FVector4& X, const FVector4& Y, const FVector4& Z, const FVector4& W)
{
	std::memcpy(&M00, &X, 4 * sizeof(float));
	std::memcpy(&M10, &Y, 4 * sizeof(float));
	std::memcpy(&M20, &Z, 4 * sizeof(float));
	std::memcpy(&M30, &W, 4 * sizeof(float));
}

FORCEINLINE FMatrix4x4::FMatrix4x4(const float InM00, const float InM01, const float InM02, const float InM03,
											  const float InM10, const float InM11, const float InM12, const float InM13,
											  const float InM20, const float InM21, const float InM22, const float InM23,
											  const float InM30, const float InM31, const float InM32, const float InM33)
{
	M00 = InM00; M01 = InM01; M02 = InM02; M03 = InM03;
	M10 = InM10; M11 = InM11; M12 = InM12; M13 = InM13;
	M20 = InM20; M21 = InM21; M22 = InM22; M23 = InM23;
	M30 = InM30; M31 = InM31; M32 = InM32; M33 = InM33;
}

FORCEINLINE FMatrix4x4 FMatrix4x4::operator*(const FMatrix4x4& Other) const
{
	return FMatrix4x4
	(
		M00 * Other.M00 + M10 * Other.M01 + M20 * Other.M02 + M30 * Other.M03,
		M01 * Other.M00 + M11 * Other.M01 + M21 * Other.M02 + M31 * Other.M03,
		M02 * Other.M00 + M12 * Other.M01 + M22 * Other.M02 + M32 * Other.M03,
		M03 * Other.M00 + M13 * Other.M01 + M23 * Other.M02 + M33 * Other.M03,
		M00 * Other.M10 + M10 * Other.M11 + M20 * Other.M12 + M30 * Other.M13,
		M01 * Other.M10 + M11 * Other.M11 + M21 * Other.M12 + M31 * Other.M13,
		M02 * Other.M10 + M12 * Other.M11 + M22 * Other.M12 + M32 * Other.M13,
		M03 * Other.M10 + M13 * Other.M11 + M23 * Other.M12 + M33 * Other.M13,
		M00 * Other.M20 + M10 * Other.M21 + M20 * Other.M22 + M30 * Other.M23,
		M01 * Other.M20 + M11 * Other.M21 + M21 * Other.M22 + M31 * Other.M23,
		M02 * Other.M20 + M12 * Other.M21 + M22 * Other.M22 + M32 * Other.M23,
		M03 * Other.M20 + M13 * Other.M21 + M23 * Other.M22 + M33 * Other.M23,
		M00 * Other.M30 + M10 * Other.M31 + M20 * Other.M32 + M30 * Other.M33,
		M01 * Other.M30 + M11 * Other.M31 + M21 * Other.M32 + M31 * Other.M33,
		M02 * Other.M30 + M12 * Other.M31 + M22 * Other.M32 + M32 * Other.M33,
		M03 * Other.M30 + M13 * Other.M31 + M23 * Other.M32 + M33 * Other.M33
	);
}

FORCEINLINE FMatrix4x4 FMatrix4x4::operator+(const FMatrix4x4& Other) const
{
	return FMatrix4x4
	(
		M00 + Other.M00, M01 + Other.M01, M02 + Other.M02, M03 + Other.M03,
		M10 + Other.M10, M11 + Other.M11, M12 + Other.M12, M13 + Other.M13,
		M20 + Other.M20, M21 + Other.M21, M22 + Other.M22, M23 + Other.M23,
		M30 + Other.M30, M31 + Other.M31, M32 + Other.M32, M33 + Other.M33
	);
}

FORCEINLINE FMatrix4x4 FMatrix4x4::operator-(const FMatrix4x4& Other) const
{
	return FMatrix4x4
	(
		M00 - Other.M00, M01 - Other.M01, M02 - Other.M02, M03 - Other.M03,
		M10 - Other.M10, M11 - Other.M11, M12 - Other.M12, M13 - Other.M13,
		M20 - Other.M20, M21 - Other.M21, M22 - Other.M22, M23 - Other.M23,
		M30 - Other.M30, M31 - Other.M31, M32 - Other.M32, M33 - Other.M33
	);
}

FORCEINLINE FMatrix4x4 FMatrix4x4::operator*(const float Scale) const
{
	return FMatrix4x4
	(
		M00 * Scale, M01 * Scale, M02 * Scale, M03 * Scale,
		M10 * Scale, M11 * Scale, M12 * Scale, M13 * Scale,
		M20 * Scale, M21 * Scale, M22 * Scale, M23 * Scale,
		M30 * Scale, M31 * Scale, M32 * Scale, M33 * Scale
	);
}

FORCEINLINE FMatrix4x4 FMatrix4x4::operator/(const float Scale) const
{
	return FMatrix4x4
	(
		M00 / Scale, M01 / Scale, M02 / Scale, M03 / Scale,
		M10 / Scale, M11 / Scale, M12 / Scale, M13 / Scale,
		M20 / Scale, M21 / Scale, M22 / Scale, M23 / Scale,
		M30 / Scale, M31 / Scale, M32 / Scale, M33 / Scale
	);
}

FORCEINLINE FVector4 FMatrix4x4::operator*(const FVector4& V) const
{
	return FVector4
	(
		M00 * V.X + M01 * V.Y + M02 * V.Z + M03 * V.W,
		M10 * V.X + M11 * V.Y + M12 * V.Z + M13 * V.W,
		M20 * V.X + M21 * V.Y + M22 * V.Z + M23 * V.W,
		M30 * V.X + M31 * V.Y + M32 * V.Z + M33 * V.W
	);
}

FORCEINLINE FMatrix4x4 FMatrix4x4::GetTranspose() const
{
	return FMatrix4x4(M00, M10, M20, M30, M01, M11, M21, M31, M02, M12, M22, M32, M03, M13, M23, M33);
}

FORCEINLINE void FMatrix4x4::CopyTo(float** Buffer) const
{
	if (Buffer == nullptr)
	{
		return;
	}
	std::memcpy(Buffer, &M00, 16 * sizeof(float));
}