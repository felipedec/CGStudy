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
#include "Vector2.h"

struct FMatrix2x2
{
public:

	/** Componentes da primeira linha */
	float M00, M01;

	/** Componentes da segunda linha */
	float M10, M11;

public:
	
	/** Matríz identidade */
	static FMatrix2x2 Identy;

public:

	/** Construtor sem inicialização dos componentes */
	FORCEINLINE FMatrix2x2() = default;

	/** Construtor passando cada componente da matríz */
	FORCEINLINE FMatrix2x2(const float In00, const float In01, const float In10, const float In11);

public:

	/**
	 * Obtem o resultado da multiplicação dessa matríz com outra.
	 *
	 * @param Other Outra matríz da operação.
	 * @return Resultado da multiplicação entre as matrízes.
	 */
	FORCEINLINE FMatrix2x2 operator*(const FMatrix2x2& Other) const;

	/**
	 * Obtem o resultado da multiplicação dessa matríz com uma escalar.
	 *
	 * @param Scale Escalar.
	 * @return Resultado da multiplicação da matríz pela escalar.
	 */
	FORCEINLINE FMatrix2x2 operator*(const float Scale) const;

	/**
	 * Obtem o resultado da divisão dessa matríz com uma escalar.
	 *
	 * @param Scale Escalar.
	 * @return Resultado da divisão da matríz pela escalar.
	 */
	FORCEINLINE FMatrix2x2 operator/(const float Scale) const;

	/**
	 * Obtem uma matríz sendo cada componente a soma dos respectivos componentes desta matríz e a outra.
	 *
	 * @param Other Outra matríz.
	 * @return Matríz com a soma dos componentes.
	 */
	FORCEINLINE FMatrix2x2 operator+(const FMatrix2x2& Other) const;

	/**
	 * Obtem uma matríz sendo cada componente a subtração dos respectivos componentes desta matríz e a outra.
	 *
	 * @param Other Outra matríz.
	 * @return Matríz com a subtração dos componentes.
	 */
	FORCEINLINE FMatrix2x2 operator-(const FMatrix2x2& Other) const;

	/**
	 * Obtem o resultado do produto da matríz com um vetor de 2 componentes.
	 *
	 * @param V Vetor.
	 * @return O resultado do produto da matríz com um vetor.
	 */
	FORCEINLINE FVector2 operator*(const FVector2& V) const;

public:

	/** Obtém uma cópia desta matríz transposta */
	FORCEINLINE FMatrix2x2 GetTranspose() const;

	/** Copiar os componente em um vetor */
	FORCEINLINE void CopyTo(float** Buffer) const;
};

/* ---------------- Inline functions ---------------- */

FORCEINLINE FMatrix2x2::FMatrix2x2(const float InM00, const float InM01, const float InM10, const float InM11)
{
	M00 = InM00;
	M01 = InM01;
	M10 = InM10;
	M11 = InM11;
}

FORCEINLINE FMatrix2x2 FMatrix2x2::operator*(const FMatrix2x2& Other) const
{
	return FMatrix2x2
	(
		M00 * Other.M00 + M01 * Other.M10,
		M00 * Other.M01 + M01 * Other.M11,
		M10 * Other.M00 + M11 * Other.M10,
		M10 * Other.M01 + M10 * Other.M01
	);
}

FORCEINLINE FMatrix2x2 FMatrix2x2::operator+(const FMatrix2x2& Other) const
{
	return FMatrix2x2(Other.M00 + M00, Other.M01 + M01, Other.M10 + M10, Other.M11 + M11);
}

FORCEINLINE FMatrix2x2 FMatrix2x2::operator-(const FMatrix2x2& Other) const
{
	return FMatrix2x2(Other.M00 - M00, Other.M01 - M01, Other.M10 - M10, Other.M11 - M11);
}

FORCEINLINE FMatrix2x2 FMatrix2x2::operator*(const float Scale) const
{
	return FMatrix2x2(M00 * Scale, M01 * Scale, M10 * Scale, M11 * Scale);
}

FORCEINLINE FMatrix2x2 FMatrix2x2::operator/(const float Scale) const
{
	return FMatrix2x2(M00 / Scale, M01 / Scale, M10 / Scale, M11 / Scale);
}

FORCEINLINE FVector2 FMatrix2x2::operator*(const FVector2& V) const
{
	return FVector2(V.X * M00 + V.Y + M01, V.X * M10 + V.Y * M11);
}

FORCEINLINE FMatrix2x2 FMatrix2x2::GetTranspose() const
{
	return FMatrix2x2(M00, M10, M01, M11);
}

FORCEINLINE void FMatrix2x2::CopyTo(float** Buffer) const
{
	if (Buffer == nullptr)
	{
		return;
	}

	std::memcpy(Buffer, &M00, 4 * sizeof(float));
}