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

struct FVector4
{
public:

	/** Componente X do vetor. */
	float X;

	/** Componente Y do vetor. */
	float Y;

	/** Componente Z do vetor. */
	float Z;

	/** Componente W do vetor. */
	float W;

public:

	/** Vetor global com todos componentes iguais a zero. */
	static const FVector4 Zero;

	/** Vetor global com todos componentes iguais a um. */
	static const FVector4 One;

public:

	/** Construtor padr�o sem inicializa��o dos componentes. */
	FORCEINLINE FVector4() = default;

	/**
	*
	* Construtor utilizando valores iniciais para cada componente.
	*
	* @param InX Valor do componente X.
	* @param InY Valor do componente Y.
	* @param InZ Valor do componente Z.
	* @param InZ Valor do componente W.
	*/
	FORCEINLINE FVector4(const float InX, const float InY, const float InZ, const float InW);

public:

	/**
	*
	* Obt�m o resultado da adi��o dos dois v�rtices.
	*
	* @param V o outro v�rtice da adi��o.
	* @return O resultado da adi��o dos dois v�rtices.
	*/
	FORCEINLINE FVector4 operator+(const FVector4& V) const;

	/**
	*
	* Obt�m o resultado da subitra��o dos dois vetores.
	*
	* @param V O outro vetor da adi��o.
	* @return O resultado da subitra��o dos dois v�rtices.
	*/
	FORCEINLINE FVector4 operator-(const FVector4& V) const;

	/**
	*
	* Obt�m o resultado da escala do vetor. (multiplicando todos os componentes por um valor).
	*
	* @param Scale Quanto devem ser multiplicado cada componente do vetor.
	* @return O resultado do vetor escalonado.
	*/
	FORCEINLINE FVector4 operator*(const float Scale) const;

	/**
	*
	* Obt�m o resultado da divis�o de todos os componente do vetor por um valor.
	*
	* @param Scale Quanto devem ser dividido cada componente do vetor.
	* @return O resultado do vetor escalonado.
	*/
	FORCEINLINE FVector4 operator/(const float Scale) const;

	/**
	*
	* Obt�m o resultado do produto escalar entre dois vetores.
	*
	* @param V O outro vetor do produto escalar.
	* @return O resutlado do produto escalar.
	*/
	FORCEINLINE float operator|(const FVector4& V) const;

public:

	/**
	*
	* Obt�m o resultado da compara��o de cada componente do vetor com outro.
	*
	* @param V O outro vetor.
	* @return Retorna verdadeiro caso todos componentes sejam iguais.
	*/
	FORCEINLINE bool operator==(const FVector4& V) const;

	/**
	*
	* Obt�m o resultado da compara��o de cada componente do vetor com outro.
	*
	* @param V O outro vetor.
	* @return Retorna faslo caso algum componente n�o seja igual.
	*/
	FORCEINLINE bool operator!=(const FVector4& V) const;

	/**
	*
	* Obt�m uma copia do vetor negativo.
	*
	* @return Copia do vetor negativo.
	*/
	FORCEINLINE FVector4 operator-() const;

	/**
	*
	* Adiciona o valor de cada componente do vetor passado
	* com os respectivos componentes deste vetor.
	*
	* @param V Vetor a ser adcionado.
	* @return Retorna a copia desse vetor ap�s a opera��o.
	*/
	FORCEINLINE FVector4 operator+=(const FVector4& V);

	/**
	*
	* Subtrair o valor de cada componente do vetor passado
	* com os respectivos componentes deste vetor.
	*
	* @param V Vetor a ser subtra�do.
	* @return Retorna a copia desse vetor ap�s a opera��o.
	*/
	FORCEINLINE FVector4 operator-=(const FVector4& V);

	/**
	*
	* Multiplica cada componente do vetor por um valor.
	*
	* @param Scale O quanto multiplicar os componentes.
	* @return Retorna a copia desse vetor ap�s a opera��o.
	*/
	FORCEINLINE FVector4 operator*=(float Scale);

	/**
	*
	* Divide cada componente do vetor por um valor.
	*
	* @param Scale O quanto dividir os componentes.
	* @return Retorna a copia desse vetor ap�s a opera��o.
	*/
	FORCEINLINE FVector4 operator/=(float Scale);

	/**
	*
	* Obt�m a refer�ncia de um componente pelo seu �ndice.
	*
	* @param Index Ind�ce do componente.
	* @return Refer�ncia do componente.
	*/
	FORCEINLINE float& operator[](int32_t Index);

	/**
	*
	* Obt�m o valor de um componente pelo seu �ndice.
	*
	* @param Index Ind�ce do componente.
	* @return Valor do componente.
	*/
	FORCEINLINE float operator[](int32_t Index) const;

public:

	/**
	* Obt�m o resultado da compara��o de cada componente do vetor com outro, com toler�ncia.
	*
	* @param V				Vetor a ser comparado.
	* @param Tolerance	Toler�ncia.
	* @retrun Retorna verdadeiro caso os vetores estejam perto suficiente.
	*/
	FORCEINLINE bool Equals(const FVector4& V, const float Tolerance) const;

	/** Retorna a magnitude do vetor ao quadrado */
	FORCEINLINE float MagnitudeSquared() const;

	/** Retorna a magnitude do vetor */;
	FORCEINLINE float Magnitude() const;

	/** Retorna uma copia do vetor normalizado */
	FORCEINLINE FVector4 GetNormalized() const;

	/** Normaliza o vetor e retorna uma copia dele */
	FORCEINLINE FVector4 Normalize();

	/** Copiar os componente em um vetor */
	FORCEINLINE void CopyTo(float Buffer[]) const;

public:

};

/* ---------------- Inline functions ---------------- */

FORCEINLINE FVector4::FVector4(const float InX, const float InY, const float InZ, const float InW)
{
	X = InX;
	Y = InY;
	Z = InZ;
	W = InW;
}

FORCEINLINE bool FVector4::Equals(const FVector4 & V, const float Tolerance) const
{
	return FMath::Abs(X - V.X) <= Tolerance && FMath::Abs(Y - V.Y) <= Tolerance 
		&& FMath::Abs(Z - V.Z) <= Tolerance && FMath::Abs(W - V.W) <= Tolerance;
}

FORCEINLINE FVector4 FVector4::operator+(const FVector4& V) const
{
	return FVector4(X + V.X, Y + V.Y, Z + V.Z, W + V.W);
}

FORCEINLINE FVector4 FVector4::operator-(const FVector4& V) const
{
	return FVector4(X - V.X, Y - V.Y, Z - V.Z, W - V.W);
}

FORCEINLINE FVector4 FVector4::operator*(const float Scale) const
{
	return FVector4(X * Scale, Y * Scale, Z * Scale, W * Scale);
}

FORCEINLINE FVector4 FVector4::operator/(const float Scale) const
{
	return FVector4(X / Scale, Y / Scale, Z / Scale, W / Scale);
}

FORCEINLINE float FVector4::operator|(const FVector4& V) const
{
	return X * V.X + Y * V.Y + Z * V.Z + W * V.W;
}


FORCEINLINE bool FVector4::operator==(const FVector4& V) const
{
	return X == V.X && Y == V.X && Z == V.Z && W == V.W;
}

FORCEINLINE bool FVector4::operator!=(const FVector4& V) const
{
	return X != V.X || Y != V.Y || Z != V.Z || W != V.W;
}

FORCEINLINE FVector4 FVector4::operator-() const
{
	return FVector4(-X, -Y, -Z, -W);
}

FORCEINLINE FVector4 FVector4::operator+=(const FVector4& V)
{
	return *this = *this + V;
}

FORCEINLINE FVector4 FVector4::operator-=(const FVector4& V)
{
	return *this = *this - V;
}

FORCEINLINE FVector4 FVector4::operator*=(float Scale)
{
	return *this = *this * Scale;
}

FORCEINLINE FVector4 FVector4::operator/=(float Scale)
{
	return *this = *this / Scale;
}

FORCEINLINE float& FVector4::operator[](int32_t Index)
{
	return (&X)[Index];
}

FORCEINLINE float FVector4::operator[](int32_t Index) const
{
	return (&X)[Index];
}

FORCEINLINE float FVector4::MagnitudeSquared() const
{
	return FMath::Square(X) + FMath::Square(Y) + FMath::Square(Z) + FMath::Sqrt(W);
}

FORCEINLINE float FVector4::Magnitude() const
{
	return FMath::Sqrt(MagnitudeSquared());
}

FORCEINLINE FVector4 FVector4::GetNormalized() const
{
	return *this / Magnitude();
}

FORCEINLINE FVector4 FVector4::Normalize()
{
	return *this = GetNormalized();
}

FORCEINLINE void FVector4::CopyTo(float Buffer[]) const
{
	if (Buffer)
	{
		Buffer[0] = X;
		Buffer[1] = Y;
		Buffer[2] = Z;
		Buffer[3] = W;
	}
}