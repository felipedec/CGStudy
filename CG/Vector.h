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

#include "Core.h"
#include "CoreFwd.h"

struct FVector
{
public:

	union
	{
		struct
		{
			/** Componente X do vetor. */
			float X;

			/** Componente Y do vetor. */
			float Y;

			/** Componente Z do vetor. */
			float Z;
		};

		struct
		{
			float Components[3];
		};
	};

public:

	/** Vetor global com todos componentes iguais a zero. */
	static CORE_API const FVector Zero;

	/** Vetor global com todos componentes iguais a um. */
	static CORE_API const FVector One;

	/** Vetor global normalizado direcionado para direita */
	static CORE_API const FVector Right;

	/** Vetor global normalizado direcionado para esquerda */
	static CORE_API const FVector Left;

	/** Vetor global normalizado direcionado para cima */
	static CORE_API const FVector Up;

	/** Vetor global normalizado direcionado para baixo */
	static CORE_API const FVector Down;

	/** Vetor global normalizado direcionado para trás */
	static CORE_API const FVector Back;

	/** Vetor global normalizado direcionado para frente */
	static CORE_API const FVector Forward;

public:

	/** Construtor padrão sem inicialização dos componentes. */
	FORCEINLINE FVector() = default;

	/**
	 * Construtor utilizando valores iniciais para cada componente.
	 *
	 * @param InX Valor do componente X.
	 * @param InY Valor do componente Y.
	 * @param InZ Valor do componente Z.
	 */
	FORCEINLINE FVector(const float InX, const float InY, const float InZ);

	/**
	 * Construtor, Passando um vetor de 4 dimensões.
	 *
	 * @param InVector Vetor refência.
	 */
	FORCEINLINE FVector(const FVector4& InVector);

	/**
	* Construtor de copia.
	*
	* @param InOther Vetor refência.
	*/
	FORCEINLINE FVector(const FVector& InOther);

public:

	/**
	 * Obtém o resultado da adição dos dois vértices.
	 *
	 * @param V o outro vértice da adição.
	 * @return O resultado da adição dos dois vértices.
	 */
	FORCEINLINE FVector operator+(const FVector& V) const;

	/**
	 * Obtém o resultado da subitração dos dois vetores.
	 *
	 * @param V O outro vetor da adição.
	 * @return O resultado da subitração dos dois vértices.
	 */
	FORCEINLINE FVector operator-(const FVector& V) const;

	/**
	 * Obtém o resultado da escala do vetor. (multiplicando todos os componentes por um valor).
	 *
	 * @param Scale Quanto devem ser multiplicado cada componente do vetor.
	 * @return O resultado do vetor escalonado.
	 */
	FORCEINLINE FVector operator*(const float Scale) const;

	/**
	 * Obtém o resultado da divisão de todos os componente do vetor por um valor.
	 *
	 * @param Scale Quanto devem ser dividido cada componente do vetor.
	 * @return O resultado do vetor escalonado.
	 */
	FORCEINLINE FVector operator/(const float Scale) const;

	/**
	 * Obtém o resultado do produto escalar entre dois vetores.
	 *
	 * @param V O outro vetor do produto escalar.
	 * @return O resutlado do produto escalar.
	 */
	FORCEINLINE float operator|(const FVector& V) const;

	/**
	 * Obtém o resultado do produto vetorial entre dois vetores.
	 *
	 * @param V O outro vetor do produto vetorial.
	 * @return O resutlado do produto vetorial.
	 */
	FORCEINLINE FVector operator^(const FVector& V) const;

public:

	/**
	 * Obtém o resultado da comparação de cada componente do vetor com outro.
	 *
	 * @param V O outro vetor.
	 * @return Retorna verdadeiro caso todos componentes sejam iguais.
	 */
	FORCEINLINE bool operator==(const FVector& V) const;

	/**
	 * Obtém o resultado da comparação de cada componente do vetor com outro.
	 *
	 * @param V O outro vetor.
	 * @return Retorna faslo caso algum componente não seja igual.
	 */
	FORCEINLINE bool operator!=(const FVector& V) const;

	/**
	 * Obtém uma copia do vetor negativo.
	 *
	 * @return Copia do vetor negativo.
	 */
	FORCEINLINE FVector operator-() const;

	/**
	 * Adiciona o valor de cada componente do vetor passado
	 * com os respectivos componentes deste vetor.
	 *
	 * @param V Vetor a ser adcionado.
	 * @return Retorna a copia desse vetor após a operação.
	 */
	FORCEINLINE FVector operator+=(const FVector& V);

	/**
	 * Subtrair o valor de cada componente do vetor passado
	 * com os respectivos componentes deste vetor.
	 *
	 * @param V Vetor a ser subtraído.
	 * @return Retorna a copia desse vetor após a operação.
	 */
	FORCEINLINE FVector operator-=(const FVector& V);

	/**
	 * Multiplica cada componente do vetor por um valor.
	 *
	 * @param Scale O quanto multiplicar os componentes.
	 * @return Retorna a copia desse vetor após a operação.
	 */
	FORCEINLINE FVector operator*=(float Scale);

	/**
	 * Divide cada componente do vetor por um valor.
	 *
	 * @param Scale O quanto dividir os componentes.
	 * @return Retorna a copia desse vetor após a operação.
	 */
	FORCEINLINE FVector operator/=(float Scale);

	/**
	 * Obtém a referência de um componente pelo seu índice.
	 *
	 * @param Index Indíce do componente.
	 * @return Referência do componente.
	 */
	FORCEINLINE float& operator[](int32_t Index);

	/**
	 * Obtém o valor de um componente pelo seu índice.
	 *
	 * @param Index Indíce do componente.
	 * @return Valor do componente.
	 */
	FORCEINLINE float operator[](int32_t Index) const;

public:

	/** Obtém uma copia desse vetor convertida para um vetor de dois componentes */
	FORCEINLINE operator FVector2() const;

public:

	/**
	 * Obtém o resultado da comparação de cada componente do vetor com outro, com tolerância.
	 *
	 * @param V				Vetor a ser comparado.
	 * @param Tolerance	Tolerância.
	 * @retrun Retorna verdadeiro caso os vetores estejam perto suficiente.
	 */
	FORCEINLINE bool Equals(const FVector& V, const float Tolerance = FMath::KindaSmallNumber) const;

	/** Retorna a magnitude do vetor ao quadrado */
	FORCEINLINE float SquaredMagnitude() const;

	/** Retorna a magnitude do vetor */;
	FORCEINLINE float Magnitude() const;

	/** Retorna uma copia do vetor normalizado */
	FORCEINLINE FVector GetNormalized() const;

	/**
	 * Obtém um versão normalizada desse vetor, verificando se o comprimento está correto
	 * 
	 * @return Um vetor normaliazado, caso contrário (0, 0, 0).
	 */
	FORCEINLINE FVector GetSafeNormal(float Tolerance = FMath::SmallNumber) const;

	/** Normaliza o vetor e retorna uma copia dele */
	FORCEINLINE FVector Normalize();

public:

	/**
	 * Obtém a distância entre doís vetores.
	 *
	 * @param V1 Primeiro vetor.
	 * @param V2 Segundo vetor.
	 * @return Distância dos doís vetores.
	 */
	FORCEINLINE static float Distance(const FVector& V1, const FVector& V2);
};

/* ---------------- Inline functions ---------------- */

#include "Vector4.h"
#include "Vector2.h"


FORCEINLINE FVector::FVector(const float InX, const float InY, const float InZ) :
	X(InX),
	Y(InY),
	Z(InZ)
{
}

FORCEINLINE FVector::FVector(const FVector4& InVector) :
	X(InVector.X),
	Y(InVector.Y),
	Z(InVector.Z)
{
}

inline FVector::FVector(const FVector& InOther) :
	X(InOther.X),
	Y(InOther.Y),
	Z(InOther.Z)
{
}

FORCEINLINE float FVector::Distance(const FVector& V1, const FVector& V2)
{
	return 1 / FMath::InvSqrt((V1 - V2).SquaredMagnitude());
}

FORCEINLINE bool FVector::Equals(const FVector & V, const float Tolerance) const
{
	return FMath::Abs(X - V.X) <= Tolerance && FMath::Abs(Y - V.Y) <= Tolerance && FMath::Abs(Z - V.Z) <= Tolerance;
}

FORCEINLINE FVector FVector::operator+(const FVector& V) const
{
	return FVector(X + V.X, Y + V.Y, Z + V.Z);
}

FORCEINLINE FVector FVector::operator-(const FVector& V) const
{
	return FVector(X - V.X, Y - V.Y, Z - V.Z);
}

FORCEINLINE FVector FVector::operator*(const float Scale) const
{
	return FVector(X * Scale, Y * Scale, Z * Scale);
}

FORCEINLINE FVector FVector::operator/(const float Scale) const
{
	return FVector(X / Scale, Y / Scale, Z / Scale);
}

FORCEINLINE float FVector::operator|(const FVector& V) const
{
	return X * V.X + Y * V.Y + Z * V.Z;
}

FORCEINLINE FVector FVector::operator^(const FVector& V) const
{
	return FVector(Y * V.Z - V.Y * Z, V.X * Z - X * V.Z, X * V.Y - V.X * Y);
}

FORCEINLINE bool FVector::operator==(const FVector& V) const
{
	return X == V.X && Y == V.X && Z == V.Z;
}

FORCEINLINE bool FVector::operator!=(const FVector& V) const
{
	return X != V.X || Y != V.Y || Z != V.Z;
}

FORCEINLINE FVector FVector::operator-() const
{
	return FVector(-X, -Y, -Z);
}

FORCEINLINE FVector FVector::operator+=(const FVector& V)
{
	return *this = *this + V;
}

FORCEINLINE FVector FVector::operator-=(const FVector& V)
{
	return *this = *this - V;
}

FORCEINLINE FVector FVector::operator*=(float Scale)
{
	return *this = *this * Scale;
}

FORCEINLINE FVector FVector::operator/=(float Scale)
{
	return *this = *this / Scale;
}

FORCEINLINE float& FVector::operator[](int32_t Index)
{
	return Components[Index];
}

FORCEINLINE float FVector::operator[](int32_t Index) const
{
	return Components[Index];
}

FORCEINLINE FVector::operator FVector2() const
{
	return FVector2(X, Y);
}

FORCEINLINE float FVector::SquaredMagnitude() const
{
	return FMath::Square(X) + FMath::Square(Y) + FMath::Square(Z);
}

FORCEINLINE float FVector::Magnitude() const
{
	return FMath::Sqrt(SquaredMagnitude());
}

FORCEINLINE FVector FVector::GetNormalized() const
{
	return *this / Magnitude();
}

FORCEINLINE FVector FVector::Normalize()
{
	return *this = GetNormalized();
}

FORCEINLINE FVector FVector::GetSafeNormal(float Tolerance) const
{
	const float SqrdMagnitude =  SquaredMagnitude();

	if (SqrdMagnitude == 1.0f)
	{
		return *this;
	}
	else if (SqrdMagnitude < Tolerance)
	{
		return FVector::Zero;
	}

	const float Scale = FMath::InvSqrt(SqrdMagnitude);
	return FVector(X * Scale, Y * Scale, Z * Scale);
}