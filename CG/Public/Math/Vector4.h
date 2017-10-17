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
#include "Vector2.h"

MS_ALIGN(16) struct FVector4
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

			/** Componente W do vetor. */
			float W;
		};

		struct
		{
			float Components[4];
		};
	};

public:

	/** Vetor global com todos componentes iguais a zero. */
	CORE_API static const FVector4 Zero;

	/** Vetor global com todos componentes iguais a um. */
	CORE_API static const FVector4 One;

public:

	/** Construtor padrão sem inicialização dos componentes. */
	FORCEINLINE FVector4() = default;

	/** Construtor utilizando valores iniciais para cada componente. */
	FORCEINLINE FVector4(const float InX, const float InY, const float InZ, const float InW);

public:

	/**
	 * Obtém o resultado da adição dos dois vértices.
	 *
	 * @param V o outro vértice da adição.
	 * @return O resultado da adição dos dois vértices.
	 */
	FORCEINLINE FVector4 operator+(const FVector4& V) const;

	/**
	 * Obtém o resultado da subitração dos dois vetores.
	 *
	 * @param V O outro vetor da adição.
	 * @return O resultado da subitração dos dois vértices.
	 */
	FORCEINLINE FVector4 operator-(const FVector4& V) const;

	/**
	 * Obtém o resultado da escala do vetor. (multiplicando todos os componentes por um valor).
	 *
	 * @param Scale Quanto devem ser multiplicado cada componente do vetor.
	 * @return O resultado do vetor escalonado.
	 */
	FORCEINLINE FVector4 operator*(const float Scale) const;

	/**
	 * Obtém o resultado da divisão de todos os componente do vetor por um valor.
	 *
	 * @param Scale Quanto devem ser dividido cada componente do vetor.
	 * @return O resultado do vetor escalonado.
	 */
	FORCEINLINE FVector4 operator/(const float Scale) const;

	/**
	 * Obtém o resultado do produto escalar entre dois vetores.
	 *
	 * @param V O outro vetor do produto escalar.
	 * @return O resutlado do produto escalar.
	 */
	FORCEINLINE float operator|(const FVector4& V) const;

public:

	/**
	 * Obtém o resultado da comparação de cada componente do vetor com outro.
	 *
	 * @param V O outro vetor.
	 * @return Retorna verdadeiro caso todos componentes sejam iguais.
	 */
	FORCEINLINE bool operator==(const FVector4& V) const;

	/**
	 * Obtém o resultado da comparação de cada componente do vetor com outro.
	 *
	 * @param V O outro vetor.
	 * @return Retorna faslo caso algum componente não seja igual.
	 */
	FORCEINLINE bool operator!=(const FVector4& V) const;

	/**
	 * Obtém uma copia do vetor negativo.
	 *
	 * @return Copia do vetor negativo.
	 */
	FORCEINLINE FVector4 operator-() const;

	/**
	 * Adiciona o valor de cada componente do vetor passado
	 * com os respectivos componentes deste vetor.
	 *
	 * @param V Vetor a ser adcionado.
	 * @return Retorna a copia desse vetor após a operação.
	 */
	FORCEINLINE FVector4 operator+=(const FVector4& V);

	/**
	 * Subtrair o valor de cada componente do vetor passado
	 * com os respectivos componentes deste vetor.
	 *
	 * @param V Vetor a ser subtraído.
	 * @return Retorna a copia desse vetor após a operação.
	 */
	FORCEINLINE FVector4 operator-=(const FVector4& V);

	/**
	 * Multiplica cada componente do vetor por um valor.
	 *
	 * @param Scale O quanto multiplicar os componentes.
	 * @return Retorna a copia desse vetor após a operação.
	 */
	FORCEINLINE FVector4 operator*=(float Scale);

	/**
	 * Divide cada componente do vetor por um valor.
	 *
	 * @param Scale O quanto dividir os componentes.
	 * @return Retorna a copia desse vetor após a operação.
	 */
	FORCEINLINE FVector4 operator/=(float Scale);

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

	/** Obtém uma copia desse vetor convertida para um vetor de três componentes */
	FORCEINLINE operator FVector() const;

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
	FORCEINLINE bool Equals(const FVector4& V, const float Tolerance) const;

	/** Retorna a magnitude do vetor ao quadrado */
	FORCEINLINE float MagnitudeSquared() const;

	/** Retorna a magnitude do vetor */;
	FORCEINLINE float Magnitude() const;

	/** Retorna uma copia do vetor normalizado */
	FORCEINLINE FVector4 GetNormalized() const;

	/** Normaliza o vetor e retorna uma copia dele */
	FORCEINLINE FVector4 Normalize();

public:

	FORCEINLINE static FVector4 Lerp(const FVector4& Lhs, const FVector4& Rhs, float T);

} GCC_ALIGN(16);

/* ---------------- Inline functions ---------------- */

#include "Math/Vector.h"

FORCEINLINE FVector4::FVector4(const float InX, const float InY, const float InZ, const float InW) :
	X(InX),
	Y(InY),
	Z(InZ),
	W(InW)
{
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
	return Components[Index];
}

FORCEINLINE float FVector4::operator[](int32_t Index) const
{
	return Components[Index];
}

FORCEINLINE FVector4::operator FVector() const
{
	return FVector(X, Y, Z);
}

FORCEINLINE FVector4::operator FVector2() const
{
	return FVector2(X, Y);
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

FORCEINLINE FVector4 FVector4::Lerp(const FVector4& Lhs, const FVector4& Rhs, float T)
{
	T = FMath::Clamp01(T);
	return Lhs * (1 - T) + Rhs * T;
}


/* ---------------- Global operators functions ---------------- */

template<typename T>
FORCEINLINE FVector4 operator*(const T& Scalar, const FVector4& V)
{
	static_assert(TIsArithmetic<T>::Value, "T must be a arithmetic type.")

		return V * Scalar;
}