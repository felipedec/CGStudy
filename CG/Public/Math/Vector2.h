/*----------------------------------------------------------------------------
			Este c�digo pertence a um projeto pessoal,
			baseado no c�digo aberto da Unreal Engine,
			com o intuito de aprendizado. Apenas as
			estrutura b�sica das classes s�o semelhantes
			e as vezes iguais, j� os corpos de m�todos
			s�o implementa��es pr�prias do desenvolvedor
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

	/** Construtor padr�o sem inicializa��o dos componentes. */
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
	 * Obt�m o resultado da adi��o dos dois v�rtices.
	 *
	 * @param V o outro v�rtice da adi��o.
	 * @return O resultado da adi��o dos dois v�rtices.
	 */
	FORCEINLINE FVector2 operator+(const FVector2& V) const;

	/**
	 *
	 * Obt�m o resultado da subitra��o dos dois vetores.
	 *
	 * @param V O outro vetor da adi��o.
	 * @return O resultado da subitra��o dos dois v�rtices.
	 */
	FORCEINLINE FVector2 operator-(const FVector2& V) const;

	/**
	 *
	 * Obt�m o resultado da escala do vetor. (multiplicando todos os componentes por um valor).
	 *
	 * @param Scale Quanto devem ser multiplicado cada componente do vetor.
	 * @return O resultado do vetor escalonado.
	 */
	FORCEINLINE FVector2 operator*(const float Scale) const;

	/**
	 *
	 * Obt�m o resultado da divis�o de todos os componente do vetor por um valor.
	 *
	 * @param Scale Quanto devem ser dividido cada componente do vetor.
	 * @return O resultado do vetor escalonado.
	 */
	FORCEINLINE FVector2 operator/(const float Scale) const;

	/**
	 *
	 * Obt�m o resultado do produto escalar entre dois vetores.
	 *
	 * @param V O outro vetor do produto escalar.
	 * @return O resutlado do produto escalar.
	 */
	FORCEINLINE float operator|(const FVector2& V) const;

public:

	/**
	 *
	 * Obt�m o resultado da compara��o de cada componente do vetor com outro.
	 *
	 * @param V O outro vetor.
	 * @return Retorna verdadeiro caso todos componentes sejam iguais.
	 */
	FORCEINLINE bool operator==(const FVector2& V) const;

	/**
	 *
	 * Obt�m o resultado da compara��o de cada componente do vetor com outro.
	 *
	 * @param V O outro vetor.
	 * @return Retorna faslo caso algum componente n�o seja igual.
	 */
	FORCEINLINE bool operator!=(const FVector2& V) const;

	/**
	 *
	 * Obt�m uma copia do vetor negativo.
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
	 * @return Retorna a copia desse vetor ap�s a opera��o.
	 */
	FORCEINLINE FVector2 operator+=(const FVector2& V);

	/**
	 *
	 * Subtrair o valor de cada componente do vetor passado
	 * com os respectivos componentes deste vetor.
	 *
	 * @param V Vetor a ser subtra�do.
	 * @return Retorna a copia desse vetor ap�s a opera��o.
	 */
	FORCEINLINE FVector2 operator-=(const FVector2& V);

	/**
	 *
	 * Multiplica cada componente do vetor por um valor.
	 *
	 * @param Scale O quanto multiplicar os componentes.
	 * @return Retorna a copia desse vetor ap�s a opera��o.
	 */
	FORCEINLINE FVector2 operator*=(float Scale);

	/**
	 *
	 * Divide cada componente do vetor por um valor.
	 *
	 * @param Scale O quanto dividir os componentes.
	 * @return Retorna a copia desse vetor ap�s a opera��o.
	 */
	FORCEINLINE FVector2 operator/=(float Scale);

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
	 * Obt�m a dist�ncia quadrada entre do�s vetores.
	 *
	 * @param V1 Primeiro vetor.
	 * @param V2 Segundo vetor.
	 * @return Dist�ncia quadrada dos do�s vetores.
	 */
	FORCEINLINE static float DistSquared(const FVector2& V1, const FVector2& V2);

	/**
	 *
	 * Obt�m a dist�ncia entre do�s vetores.
	 *
	 * @param V1 Primeiro vetor.
	 * @param V2 Segundo vetor.
	 * @return Dist�ncia dos do�s vetores.
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