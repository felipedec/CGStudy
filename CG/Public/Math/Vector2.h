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

struct FVector2
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
		};

		struct
		{
			float Components[2];
		};
	};

public:

	/** Vetor global com todos componentes iguais a zero. */
	CORE_API static const FVector2 Zero;

	/** Vetor global com todos componentes iguais a um. */
	CORE_API static const FVector2 One;

	/** Vetor global com componente X igual a um e Y zero. */
	CORE_API static const FVector2 Right;

	/** Vetor global com componente X igual a menos um e Y zero. */
	CORE_API static const FVector2 Left;

	/** Vetor global com componente Y igual a um e X zero. */
	CORE_API static const FVector2 Up;

	/** Vetor global com componente menos Y igual a um e X zero. */
	CORE_API static const FVector2 Down;

public:

	/** Construtor padrão sem inicialização dos componentes. */
	FORCEINLINE FVector2() = default;

	/**
	 *
	 * Construtor utilizando valores iniciais para cada componente.
	 *
	 * @param InX Valor do componente X.
	 * @param InY Valor do componente Y.
	 */
	FORCEINLINE FVector2(const float InX, const float InY);

public:

	/**
	 *
	 * Obtém o resultado da adição dos dois vértices.
	 *
	 * @param V o outro vértice da adição.
	 * @return O resultado da adição dos dois vértices.
	 */
	FORCEINLINE FVector2 operator+(const FVector2& V) const;

	/**
	 *
	 * Obtém o resultado da subitração dos dois vetores.
	 *
	 * @param V O outro vetor da adição.
	 * @return O resultado da subitração dos dois vértices.
	 */
	FORCEINLINE FVector2 operator-(const FVector2& V) const;

	/**
	 *
	 * Obtém o resultado da escala do vetor. (multiplicando todos os componentes por um valor).
	 *
	 * @param Scale Quanto devem ser multiplicado cada componente do vetor.
	 * @return O resultado do vetor escalonado.
	 */
	FORCEINLINE FVector2 operator*(const float Scale) const;

	/**
	 *
	 * Obtém o resultado da divisão de todos os componente do vetor por um valor.
	 *
	 * @param Scale Quanto devem ser dividido cada componente do vetor.
	 * @return O resultado do vetor escalonado.
	 */
	FORCEINLINE FVector2 operator/(const float Scale) const;

	/**
	 *
	 * Obtém o resultado do produto escalar entre dois vetores.
	 *
	 * @param V O outro vetor do produto escalar.
	 * @return O resutlado do produto escalar.
	 */
	FORCEINLINE float operator|(const FVector2& V) const;

public:

	/**
	 *
	 * Obtém o resultado da comparação de cada componente do vetor com outro.
	 *
	 * @param V O outro vetor.
	 * @return Retorna verdadeiro caso todos componentes sejam iguais.
	 */
	FORCEINLINE bool operator==(const FVector2& V) const;

	/**
	 *
	 * Obtém o resultado da comparação de cada componente do vetor com outro.
	 *
	 * @param V O outro vetor.
	 * @return Retorna faslo caso algum componente não seja igual.
	 */
	FORCEINLINE bool operator!=(const FVector2& V) const;

	/**
	 *
	 * Obtém uma copia do vetor negativo.
	 *
	 * @return Copia do vetor negativo.
	 */
	FORCEINLINE FVector2 operator-() const;

	/**
	 *
	 * Adiciona o valor de cada componente do vetor passado
	 * com os respectivos componentes deste vetor.
	 *
	 * @param V Vetor a ser adcionado.
	 * @return Retorna a copia desse vetor após a operação.
	 */
	FORCEINLINE FVector2 operator+=(const FVector2& V);

	/**
	 *
	 * Subtrair o valor de cada componente do vetor passado
	 * com os respectivos componentes deste vetor.
	 *
	 * @param V Vetor a ser subtraído.
	 * @return Retorna a copia desse vetor após a operação.
	 */
	FORCEINLINE FVector2 operator-=(const FVector2& V);

	/**
	 *
	 * Multiplica cada componente do vetor por um valor.
	 *
	 * @param Scale O quanto multiplicar os componentes.
	 * @return Retorna a copia desse vetor após a operação.
	 */
	FORCEINLINE FVector2 operator*=(float Scale);

	/**
	 *
	 * Divide cada componente do vetor por um valor.
	 *
	 * @param Scale O quanto dividir os componentes.
	 * @return Retorna a copia desse vetor após a operação.
	 */
	FORCEINLINE FVector2 operator/=(float Scale);

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
	FORCEINLINE bool FVector2::Equals(const FVector2& V, const float Tolerance) const;

	/** Retorna a magnitude do vetor ao quadrado */
	FORCEINLINE float MagnitudeSquared() const;

	/** Retorna a magnitude do vetor */;
	FORCEINLINE float Magnitude() const;

	/** Retorna uma copia do vetor normalizado */
	FORCEINLINE FVector2 GetNormalized() const;

	/** Normaliza o vetor e retorna uma copia dele */
	FORCEINLINE FVector2 Normalize();

public:

	/**
	 *
	 * Obtém a distância quadrada entre doís vetores.
	 *
	 * @param V1 Primeiro vetor.
	 * @param V2 Segundo vetor.
	 * @return Distância quadrada dos doís vetores.
	 */
	FORCEINLINE static float DistSquared(const FVector2& V1, const FVector2& V2);

	/**
	 *
	 * Obtém a distância entre doís vetores.
	 *
	 * @param V1 Primeiro vetor.
	 * @param V2 Segundo vetor.
	 * @return Distância dos doís vetores.
	 */
	FORCEINLINE static float Distance(const FVector2& V1, const FVector2& V2);

public:

	FORCEINLINE static FVector2 Lerp(const FVector2& Lhs, const FVector2& Rhs, float T);

};

/* ---------------- Inline functions ---------------- */

FORCEINLINE FVector2::FVector2(const float InX, const float InY) :
	X(InX),
	Y(InY)
{
}

FORCEINLINE float FVector2::DistSquared(const FVector2 & V1, const FVector2 & V2)
{
	return FMath::Square(V1.X - V2.X) + FMath::Square(V1.Y - V2.Y);
}

FORCEINLINE float FVector2::Distance(const FVector2 & V1, const FVector2 & V2)
{
	return FMath::Sqrt(FVector2::DistSquared(V1, V2));
}

FORCEINLINE bool FVector2::Equals(const FVector2 & V, const float Tolerance) const
{
	return FMath::Abs(X - V.X) <= Tolerance && FMath::Abs(Y - V.Y) <= Tolerance;
}

FORCEINLINE FVector2 FVector2::operator+(const FVector2& V) const
{
	return FVector2(X + V.X, Y + V.Y);
}

FORCEINLINE FVector2 FVector2::operator-(const FVector2& V) const
{
	return FVector2(X - V.X, Y - V.Y);
}

FORCEINLINE FVector2 FVector2::operator*(const float Scale) const
{
	return FVector2(X * Scale, Y * Scale);
}

FORCEINLINE FVector2 FVector2::operator/(const float Scale) const
{
	return FVector2(X / Scale, Y / Scale);
}

FORCEINLINE float FVector2::operator|(const FVector2& V) const
{
	return X * V.X + Y * V.Y;
}

FORCEINLINE bool FVector2::operator==(const FVector2& V) const
{
	return X == V.X && Y == V.X;
}

FORCEINLINE bool FVector2::operator!=(const FVector2& V) const
{
	return X != V.X || Y != V.Y;
}

FORCEINLINE FVector2 FVector2::operator-() const
{
	return FVector2(-X, -Y);
}

FORCEINLINE FVector2 FVector2::operator+=(const FVector2& V)
{
	return *this = *this + V;
}

FORCEINLINE FVector2 FVector2::operator-=(const FVector2& V)
{
	return *this = *this - V;
}

FORCEINLINE FVector2 FVector2::operator*=(float Scale)
{
	return *this = *this * Scale;
}

FORCEINLINE FVector2 FVector2::operator/=(float Scale)
{
	return *this = *this / Scale;
}

FORCEINLINE float& FVector2::operator[](int32_t Index)
{
	return Components[Index];
}

FORCEINLINE float FVector2::operator[](int32_t Index) const
{
	return Components[Index];
}

FORCEINLINE float FVector2::MagnitudeSquared() const
{
	return FMath::Square(X) + FMath::Square(Y);
}

FORCEINLINE float FVector2::Magnitude() const
{
	return FMath::Sqrt(MagnitudeSquared());
}

FORCEINLINE FVector2 FVector2::GetNormalized() const
{
	return *this / Magnitude();
}

FORCEINLINE FVector2 FVector2::Normalize()
{
	return *this = GetNormalized();
}

FORCEINLINE FVector2 FVector2::Lerp(const FVector2& Lhs, const FVector2& Rhs, float T)
{
	T = FMath::Clamp01(T);
	return Lhs * (1 - T) + Rhs * T;
}


/* ---------------- Global operators functions ---------------- */

template<typename T>
FORCEINLINE FVector2 operator*(const T& Scalar, const FVector2& V)
{
	static_assert(TIsArithmetic<T>::Value, "T must be a arithmetic type.");

		return V * Scalar;
}