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

struct FVector3
{
public:

	/** Componente X do vetor. */
	float X;

	/** Componente Y do vetor. */
	float Y;

	/** Componente Z do vetor. */
	float Z;

public:

	/** Vetor global com todos componentes iguais a zero. */
	static const FVector3 Zero;

	/** Vetor global com todos componentes iguais a um. */
	static const FVector3 One;

	/** Vetor global normalizado direcionado para direita */
	static const FVector3 Right;

	/** Vetor global normalizado direcionado para esquerda */
	static const FVector3 Left;

	/** Vetor global normalizado direcionado para cima */
	static const FVector3 Up;

	/** Vetor global normalizado direcionado para baixo */
	static const FVector3 Down;

	/** Vetor global normalizado direcionado para trás */
	static const FVector3 Back;

	/** Vetor global normalizado direcionado para frente */
	static const FVector3 Forward;

public:

	/** Construtor padrão sem inicialização dos componentes. */
	FORCEINLINE FVector3() = default;

	/**
	 *
	 * Construtor utilizando valores iniciais para cada componente.
	 *
	 * @param InX Valor do componente X.
	 * @param InY Valor do componente Y.
	 * @param InZ Valor do componente Z.
	 */
	FORCEINLINE FVector3(const float InX, const float InY, const float InZ);

public:

	/**
	 *
	 * Obtém o resultado da adição dos dois vértices.
	 *
	 * @param V o outro vértice da adição.
	 * @return O resultado da adição dos dois vértices.
	 */
	FORCEINLINE FVector3 operator+(const FVector3& V) const;

	/**
	 *
	 * Obtém o resultado da subitração dos dois vetores.
	 *
	 * @param V O outro vetor da adição.
	 * @return O resultado da subitração dos dois vértices.
	 */
	FORCEINLINE FVector3 operator-(const FVector3& V) const;

	/**
	 *
	 * Obtém o resultado da escala do vetor. (multiplicando todos os componentes por um valor).
	 *
	 * @param Scale Quanto devem ser multiplicado cada componente do vetor.
	 * @return O resultado do vetor escalonado.
	 */
	FORCEINLINE FVector3 operator*(const float Scale) const;

	/**
	 *
	 * Obtém o resultado da divisão de todos os componente do vetor por um valor.
	 *
	 * @param Scale Quanto devem ser dividido cada componente do vetor.
	 * @return O resultado do vetor escalonado.
	 */
	FORCEINLINE FVector3 operator/(const float Scale) const;

	/**
	 *
	 * Obtém o resultado do produto escalar entre dois vetores.
	 *
	 * @param V O outro vetor do produto escalar.
	 * @return O resutlado do produto escalar.
	 */
	FORCEINLINE float operator|(const FVector3& V) const;

	/**
	*
	* Obtém o resultado do produto vetorial entre dois vetores.
	*
	* @param V O outro vetor do produto vetorial.
	* @return O resutlado do produto vetorial.
	*/
	FORCEINLINE FVector3 operator^(const FVector3& V) const;

public:

	/**
	 *
	 * Obtém o resultado da comparação de cada componente do vetor com outro.
	 *
	 * @param V O outro vetor.
	 * @return Retorna verdadeiro caso todos componentes sejam iguais.
	 */
	FORCEINLINE bool operator==(const FVector3& V) const;

	/**
	 *
	 * Obtém o resultado da comparação de cada componente do vetor com outro.
	 *
	 * @param V O outro vetor.
	 * @return Retorna faslo caso algum componente não seja igual.
	 */
	FORCEINLINE bool operator!=(const FVector3& V) const;

	/**
	 *
	 * Obtém uma copia do vetor negativo.
	 *
	 * @return Copia do vetor negativo.
	 */
	FORCEINLINE FVector3 operator-() const;

	 /**
	 *
	 * Adiciona o valor de cada componente do vetor passado
	 * com os respectivos componentes deste vetor.
	 *
	 * @param V Vetor a ser adcionado.
	 * @return Retorna a copia desse vetor após a operação.
	 */
	FORCEINLINE FVector3 operator+=(const FVector3& V);

	/**
	 *
	 * Subtrair o valor de cada componente do vetor passado
	 * com os respectivos componentes deste vetor.
	 *
	 * @param V Vetor a ser subtraído.
	 * @return Retorna a copia desse vetor após a operação.
	 */
	FORCEINLINE FVector3 operator-=(const FVector3& V);

	/**
	 *
	 * Multiplica cada componente do vetor por um valor.
	 *
	 * @param Scale O quanto multiplicar os componentes.
	 * @return Retorna a copia desse vetor após a operação.
	 */
	FORCEINLINE FVector3 operator*=(float Scale);

	/**
	 *
	 * Divide cada componente do vetor por um valor.
	 *
	 * @param Scale O quanto dividir os componentes.
	 * @return Retorna a copia desse vetor após a operação.
	 */
	FORCEINLINE FVector3 operator/=(float Scale);

	/**
	 *
	 * Obtém a referência de um componente pelo seu índice.
	 *
	 * @param Index Indíce do componente.
	 * @return Referência do componente.
	 */
	FORCEINLINE float& operator[](int32_t Index);

	/**
	 *
	 * Obtém o valor de um componente pelo seu índice.
	 *
	 * @param Index Indíce do componente.
	 * @return Valor do componente.
	 */
	FORCEINLINE float operator[](int32_t Index) const;

public:

	/**
	 * Obtém o resultado da comparação de cada componente do vetor com outro, com tolerância.
	 *
	 * @param V				Vetor a ser comparado.
	 * @param Tolerance	Tolerância.
	 * @retrun Retorna verdadeiro caso os vetores estejam perto suficiente.
	 */
	FORCEINLINE bool Equals(const FVector3& V, const float Tolerance) const;

	/** Retorna a magnitude do vetor ao quadrado */
	FORCEINLINE float MagnitudeSquared() const;

	/** Retorna a magnitude do vetor */;
	FORCEINLINE float Magnitude() const;

	/** Retorna uma copia do vetor normalizado */
	FORCEINLINE FVector3 GetNormalized() const;

	/** Normaliza o vetor e retorna uma copia dele */
	FORCEINLINE FVector3 Normalize();

	/** Copiar os componente em um vetor */
	FORCEINLINE void CopyTo(float Buffer[]) const;

public:

	/**
	 *
	 * Obtém a distância quadrada entre doís vetores.
	 *
	 * @param V1 Primeiro vetor.
	 * @param V2 Segundo vetor.
	 * @return Distância quadrada dos doís vetores.
	 */
	FORCEINLINE static float DistSquared(const FVector3& V1, const FVector3& V2);

	/**
	 *
	 * Obtém a distância entre doís vetores.
	 *
	 * @param V1 Primeiro vetor.
	 * @param V2 Segundo vetor.
	 * @return Distância dos doís vetores.
	 */
	FORCEINLINE static float Distance(const FVector3& V1, const FVector3& V2);
};

/* ---------------- Inline functions ---------------- */

FORCEINLINE FVector3::FVector3(const float InX, const float InY, const float InZ)
{
	X = InX;
	Y = InY;
	Z = InZ;
}

FORCEINLINE float FVector3::DistSquared(const FVector3& V1, const FVector3& V2)
{
	return (V1 - V2).MagnitudeSquared();
}

FORCEINLINE float FVector3::Distance(const FVector3& V1, const FVector3& V2)
{
	return FMath::Sqrt(FVector3::DistSquared(V1, V2));
}

FORCEINLINE bool FVector3::Equals(const FVector3 & V, const float Tolerance) const
{
	return FMath::Abs(X - V.X) <= Tolerance && FMath::Abs(Y - V.Y) <= Tolerance && FMath::Abs(Z - V.Z) <= Tolerance;
}

FORCEINLINE FVector3 FVector3::operator+(const FVector3& V) const
{
	return FVector3(X + V.X, Y + V.Y, Z + V.Z);
}

FORCEINLINE FVector3 FVector3::operator-(const FVector3& V) const
{
	return FVector3(X - V.X, Y - V.Y, Z - V.Z);
}

FORCEINLINE FVector3 FVector3::operator*(const float Scale) const
{
	return FVector3(X * Scale, Y * Scale, Z * Scale);
}

FORCEINLINE FVector3 FVector3::operator/(const float Scale) const
{
	return FVector3(X / Scale, Y / Scale, Z / Scale);
}

FORCEINLINE float FVector3::operator|(const FVector3& V) const
{
	return X * V.X + Y * V.Y + Z * V.Z;
}

FORCEINLINE FVector3 FVector3::operator^(const FVector3& V) const
{
	return FVector3(Y * V.Z - V.Y * Z, V.X * Z - X * V.Z, X * V.Y - V.X * Y);
}

FORCEINLINE bool FVector3::operator==(const FVector3& V) const
{
	return X == V.X && Y == V.X && Z == V.Z;
}

FORCEINLINE bool FVector3::operator!=(const FVector3& V) const
{
	return X != V.X || Y != V.Y || Z != V.Z;
}

FORCEINLINE FVector3 FVector3::operator-() const
{
	return FVector3(-X, -Y, -Z);
}

FORCEINLINE FVector3 FVector3::operator+=(const FVector3& V)
{
	return *this = *this + V;
}

FORCEINLINE FVector3 FVector3::operator-=(const FVector3& V)
{
	return *this = *this - V;
}

FORCEINLINE FVector3 FVector3::operator*=(float Scale)
{
	return *this = *this * Scale;
}

FORCEINLINE FVector3 FVector3::operator/=(float Scale)
{
	return *this = *this / Scale;
}

FORCEINLINE float& FVector3::operator[](int32_t Index)
{
	return (&X)[Index];
}

FORCEINLINE float FVector3::operator[](int32_t Index) const
{
	return (&X)[Index];
}

FORCEINLINE float FVector3::MagnitudeSquared() const
{
	return FMath::Square(X) + FMath::Square(Y) + FMath::Square(Z);
}

FORCEINLINE float FVector3::Magnitude() const
{
	return FMath::Sqrt(MagnitudeSquared());
}

FORCEINLINE FVector3 FVector3::GetNormalized() const
{
	return *this / Magnitude();
}

FORCEINLINE FVector3 FVector3::Normalize()
{
	return *this = GetNormalized();
}

FORCEINLINE void FVector3::CopyTo(float Buffer[]) const
{
	if (Buffer)
	{
		Buffer[0] = X;
		Buffer[1] = Y;
		Buffer[2] = Z;
	}
}