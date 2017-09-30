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

	/** Vetor global normalizado direcionado para tr�s */
	static CORE_API const FVector Back;

	/** Vetor global normalizado direcionado para frente */
	static CORE_API const FVector Forward;

public:

	/** Construtor padr�o sem inicializa��o dos componentes. */
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
	 * Construtor, Passando um vetor de 4 dimens�es.
	 *
	 * @param InVector Vetor ref�ncia.
	 */
	FORCEINLINE FVector(const FVector4& InVector);

	/**
	* Construtor de copia.
	*
	* @param InOther Vetor ref�ncia.
	*/
	FORCEINLINE FVector(const FVector& InOther);

public:

	/**
	 * Obt�m o resultado da adi��o dos dois v�rtices.
	 *
	 * @param V o outro v�rtice da adi��o.
	 * @return O resultado da adi��o dos dois v�rtices.
	 */
	FORCEINLINE FVector operator+(const FVector& V) const;

	/**
	 * Obt�m o resultado da subitra��o dos dois vetores.
	 *
	 * @param V O outro vetor da adi��o.
	 * @return O resultado da subitra��o dos dois v�rtices.
	 */
	FORCEINLINE FVector operator-(const FVector& V) const;

	/**
	 * Obt�m o resultado da escala do vetor. (multiplicando todos os componentes por um valor).
	 *
	 * @param Scale Quanto devem ser multiplicado cada componente do vetor.
	 * @return O resultado do vetor escalonado.
	 */
	FORCEINLINE FVector operator*(const float Scale) const;

	/**
	 * Obt�m o resultado da divis�o de todos os componente do vetor por um valor.
	 *
	 * @param Scale Quanto devem ser dividido cada componente do vetor.
	 * @return O resultado do vetor escalonado.
	 */
	FORCEINLINE FVector operator/(const float Scale) const;

	/**
	 * Obt�m o resultado do produto escalar entre dois vetores.
	 *
	 * @param V O outro vetor do produto escalar.
	 * @return O resutlado do produto escalar.
	 */
	FORCEINLINE float operator|(const FVector& V) const;

	/**
	 * Obt�m o resultado do produto vetorial entre dois vetores.
	 *
	 * @param V O outro vetor do produto vetorial.
	 * @return O resutlado do produto vetorial.
	 */
	FORCEINLINE FVector operator^(const FVector& V) const;

public:

	/**
	 * Obt�m o resultado da compara��o de cada componente do vetor com outro.
	 *
	 * @param V O outro vetor.
	 * @return Retorna verdadeiro caso todos componentes sejam iguais.
	 */
	FORCEINLINE bool operator==(const FVector& V) const;

	/**
	 * Obt�m o resultado da compara��o de cada componente do vetor com outro.
	 *
	 * @param V O outro vetor.
	 * @return Retorna faslo caso algum componente n�o seja igual.
	 */
	FORCEINLINE bool operator!=(const FVector& V) const;

	/**
	 * Obt�m uma copia do vetor negativo.
	 *
	 * @return Copia do vetor negativo.
	 */
	FORCEINLINE FVector operator-() const;

	/**
	 * Adiciona o valor de cada componente do vetor passado
	 * com os respectivos componentes deste vetor.
	 *
	 * @param V Vetor a ser adcionado.
	 * @return Retorna a copia desse vetor ap�s a opera��o.
	 */
	FORCEINLINE FVector operator+=(const FVector& V);

	/**
	 * Subtrair o valor de cada componente do vetor passado
	 * com os respectivos componentes deste vetor.
	 *
	 * @param V Vetor a ser subtra�do.
	 * @return Retorna a copia desse vetor ap�s a opera��o.
	 */
	FORCEINLINE FVector operator-=(const FVector& V);

	/**
	 * Multiplica cada componente do vetor por um valor.
	 *
	 * @param Scale O quanto multiplicar os componentes.
	 * @return Retorna a copia desse vetor ap�s a opera��o.
	 */
	FORCEINLINE FVector operator*=(float Scale);

	/**
	 * Divide cada componente do vetor por um valor.
	 *
	 * @param Scale O quanto dividir os componentes.
	 * @return Retorna a copia desse vetor ap�s a opera��o.
	 */
	FORCEINLINE FVector operator/=(float Scale);

	/**
	 * Obt�m a refer�ncia de um componente pelo seu �ndice.
	 *
	 * @param Index Ind�ce do componente.
	 * @return Refer�ncia do componente.
	 */
	FORCEINLINE float& operator[](int32_t Index);

	/**
	 * Obt�m o valor de um componente pelo seu �ndice.
	 *
	 * @param Index Ind�ce do componente.
	 * @return Valor do componente.
	 */
	FORCEINLINE float operator[](int32_t Index) const;

public:

	/** Obt�m uma copia desse vetor convertida para um vetor de dois componentes */
	FORCEINLINE operator FVector2() const;

public:

	/**
	 * Obt�m o resultado da compara��o de cada componente do vetor com outro, com toler�ncia.
	 *
	 * @param V				Vetor a ser comparado.
	 * @param Tolerance	Toler�ncia.
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
	 * Obt�m um vers�o normalizada desse vetor, verificando se o comprimento est� correto
	 * 
	 * @return Um vetor normaliazado, caso contr�rio (0, 0, 0).
	 */
	FORCEINLINE FVector GetSafeNormal(float Tolerance = FMath::SmallNumber) const;

	/** Normaliza o vetor e retorna uma copia dele */
	FORCEINLINE FVector Normalize();

public:

	/**
	 * Obt�m a dist�ncia entre do�s vetores.
	 *
	 * @param V1 Primeiro vetor.
	 * @param V2 Segundo vetor.
	 * @return Dist�ncia dos do�s vetores.
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