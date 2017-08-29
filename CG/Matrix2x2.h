// Este c�digo pertence a um projeto pessoal,
// baseado no c�digo aberto da Unreal Engine,
// com o intuito de aprendizado. Apenas as 
// estrutura b�sica das classes s�o semelhantes
// e as vezes iguais, j� os corpos de m�todos
// s�o implementa��es pr�prias do desenvolvedor
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
	
	/** Matr�z identidade */
	static FMatrix2x2 Identy;

public:

	/** Construtor sem inicializa��o dos componentes */
	FORCEINLINE FMatrix2x2() = default;

	/** Construtor passando cada componente da matr�z */
	FORCEINLINE FMatrix2x2(const float In00, const float In01, const float In10, const float In11);

public:

	/**
	 * Obtem o resultado da multiplica��o dessa matr�z com outra.
	 *
	 * @param Other Outra matr�z da opera��o.
	 * @return Resultado da multiplica��o entre as matr�zes.
	 */
	FORCEINLINE FMatrix2x2 operator*(const FMatrix2x2& Other) const;

	/**
	 * Obtem o resultado da multiplica��o dessa matr�z com uma escalar.
	 *
	 * @param Scale Escalar.
	 * @return Resultado da multiplica��o da matr�z pela escalar.
	 */
	FORCEINLINE FMatrix2x2 operator*(const float Scale) const;

	/**
	 * Obtem o resultado da divis�o dessa matr�z com uma escalar.
	 *
	 * @param Scale Escalar.
	 * @return Resultado da divis�o da matr�z pela escalar.
	 */
	FORCEINLINE FMatrix2x2 operator/(const float Scale) const;

	/**
	 * Obtem uma matr�z sendo cada componente a soma dos respectivos componentes desta matr�z e a outra.
	 *
	 * @param Other Outra matr�z.
	 * @return Matr�z com a soma dos componentes.
	 */
	FORCEINLINE FMatrix2x2 operator+(const FMatrix2x2& Other) const;

	/**
	 * Obtem uma matr�z sendo cada componente a subtra��o dos respectivos componentes desta matr�z e a outra.
	 *
	 * @param Other Outra matr�z.
	 * @return Matr�z com a subtra��o dos componentes.
	 */
	FORCEINLINE FMatrix2x2 operator-(const FMatrix2x2& Other) const;

	/**
	 * Obtem o resultado do produto da matr�z com um vetor de 2 componentes.
	 *
	 * @param V Vetor.
	 * @return O resultado do produto da matr�z com um vetor.
	 */
	FORCEINLINE FVector2 operator*(const FVector2& V) const;

public:

	/** Obt�m uma c�pia desta matr�z transposta */
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