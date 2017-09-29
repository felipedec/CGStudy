/*----------------------------------------------------------------------------
			Este código pertence a um projeto pessoal,
			baseado no código aberto da Unreal Engine,
			com o intuito de aprendizado. Apenas as
			estrutura básica das classes são semelhantes
			e as vezes iguais, já os corpos de métodos
			são implementações próprias do desenvolvedor
			deste projeto.
			
			Saiba mais:
			https://github.com/felipedec/CGStudy
----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------
			Este arquivo contradiz um pouco o cabeçalho, poís é basicamente
			uma tradução do Engine/Source/Runtime/Core/Public/Plane.h, já
			que não ha muito o que se diferenciar da implementação original
			da Epic Games.
----------------------------------------------------------------------------*/

#pragma once

#include "Core.h"

MS_ALIGN(16) struct FPlane : public FVector
{
public:
	
	/** Componente w do plano */
	float W;

public:

	/** Construtor padrão */
	FORCEINLINE FPlane();

	/**
	 * Construtor, definir o plano a partir de um vetor de 4 dimensões.
	 *
	 * @param Vector Vetor de quatro dimensões.
	 */
	FORCEINLINE FPlane(const FVector4& Vector);

	/**
	 * Construtor.
	 *
	 * @param InX Coeficiente X. 
	 * @param InY Coeficiente Y.
	 * @param InZ Coeficiente Z.
	 * @param InW Coeficiente W.
	 */
	FORCEINLINE FPlane(float InX, float InY, float InZ, float InW);


	/**
	 * Construtor.
	 *
	 * @param InNormal Normal do plano.
	 * @param InW Coeficiente W do plano.
	 */
	FORCEINLINE FPlane(FVector InNormal, float InW);

	/**
	 * Construtor, definir o plano a partir de 3 pontos no espaço.
	 *
	 * @param A First point in the plane.
	 * @param B Second point in the plane.
	 * @param C Third point in the plane.
	 */
	FPlane(FVector A, FVector B, FVector C);

	/**
	 * Construtor, passando um ponto pertencente ao plano e sua direção.
 	 *
	 * @param InBase Ponto base do plano.
	 * @param InNormal Direção do plano.
	 */
	FORCEINLINE FPlane(FVector InBase, const FVector &InNormal);

public:

	/**
	 * Obtém a menor distância entre um ponto e o plano.
	 *
	 * @param P O ponto.
	 * @return	>0: O ponto esta na frente do palno.
	 *				<0: O ponto esta atrás do plano.
	 *				=0: O ponto pertence ao plano.
	 */
	FORCEINLINE float PlaneDot(const FVector &P) const;

	/**
	 * Obtém uma copia desse plano com a direção invertida.
	 *
	 * @return Uma versão desse plano invertida.
	 */
	FPlane Flip() const;

public:

	/**
	 * Verificas se dois planos são iguais.
	 *
	 * @param V O outro plano.
	 * @return true se os planos forem iguais, caso contrário falso.
	 */
	bool operator==(const FPlane& V) const;

	/**
	 * Verificas se dois planos são diferentes.
	 *
	 * @param V O outro plano.
	 * @return true se os planos forem diferentes, caso contrário falso.
	 */
	bool operator!=(const FPlane& V) const;


	/**
	 * Calcula o produto escalar de dois planos.
	 *
	 * @param V O outro plano.
	 * @return O produto escalar.
	 */
	FORCEINLINE float operator|(const FPlane& V) const;

	/**
	 * Obtém o resultado da adição de dois planos.
	 *
	 * @param V O outro plano
	 * @return Resultado da adição.
	 */
	FPlane operator+(const FPlane& V) const;

	/**
	 * GObtém o resultado da subtração de dois planos.
	 *
	 * @param V O outro plano.
	 * @return Resultado da subtração.
	 */
	FPlane operator-(const FPlane& V) const;

	/**
	 * Obtém o resultado da divisão do plano por um coeficiente linear.
	 *
	 * @param Scale Divisor.
	 * @return Resultado da divisão.
	 */
	FPlane operator/(float Scale) const;

	/**
	 * Obtém o resultado da multiplicação do plano por um coeficiente linear.
	 *
	 * @param Scale Fator da multiplicação.
	 * @return Resultado da multiplicação.
	 */
	FPlane operator*(float Scale) const;

	/**
	 * Obtém o resultado da multiplicação do plano por outro plano.
	 *
	 * @param V O outro plano.
	 * @return Resultado da multiplicação.
	 */
	FPlane operator*(const FPlane& V);

	/**
	 * Adicionar outro plano a este.
	 *
	 * @param V O outro plano.
	 * @return Copia do plano depois da adição.
	 */
	FPlane operator+=(const FPlane& V);

	/**
	 * Subtrai outro plano a este.
	 *
	 * @param V O outro plano.
	 * @return Copia do plano depois da subtração.
	 */
	FPlane operator-=(const FPlane& V);

	/**
	 * Multiplicar este plano.
	 *
	 * @param Scale Fator da multiplicação.
	 * @return Copia do plano depois da multiplicação.
	 */
	FPlane operator*=(float Scale);

	/**
	 * Multiplicar outro plano a este.
	 *
	 * @param V O outro plano.
	 * @return Copia do plano depois da multiplicação.
	 */
	FPlane operator*=(const FPlane& V);

	/**
	* Dividir este plano.
	*
	* @param V Divisor.
	* @return Copia do plano depois da divisão.
	*/
	FPlane operator/=(float V);

public:

	/**
	 * Obtém o resultado da comparação de cada componente do plano com outro, com tolerância.
	 *
	 * @param V				Plano a ser comparado.
	 * @param Tolerance	Tolerância.
	 * @retrun Retorna verdadeiro caso os planos estejam perto suficiente.
	 */
	FORCEINLINE bool FPlane::Equals(const FPlane& V, float Tolerance = FMath::SmallNumber) const;

} GCC_ALIGN(16);

/* ---------------- Inline functions ---------------- */

#include "Vector.h"
#include "Vector4.h"

FORCEINLINE FPlane::FPlane()
{}

FORCEINLINE FPlane::FPlane(const FVector4& V) :
	FVector(V),
	W(V.W)
{}

FORCEINLINE FPlane::FPlane(float InX, float InY, float InZ, float InW) :
	FVector(InX, InY, InZ),
	W(InW)
{}

FORCEINLINE FPlane::FPlane(FVector InNormal, float InW) : 
	FVector(InNormal),
	W(InW)
{}

FORCEINLINE FPlane::FPlane(FVector InBase, const FVector &InNormal)
	: FVector(InNormal)
	, W(InBase | InNormal)
{}


FORCEINLINE FPlane::FPlane(FVector A, FVector B, FVector C)
	: FVector(((B - A) ^ (C - A)).GetSafeNormal())
{
	W = A | (FVector)(*this);
}

FORCEINLINE float FPlane::PlaneDot(const FVector & P) const
{
	return X * P.X + Y * P.Y + Z * P.Z - W;
}

FORCEINLINE FPlane FPlane::Flip() const
{
	return FPlane(-X, -Y, -Z, -W);
}

FORCEINLINE bool FPlane::operator==(const FPlane& V) const
{
	return (X == V.X) && (Y == V.Y) && (Z == V.Z) && (W == V.W);
}

FORCEINLINE bool FPlane::operator!=(const FPlane& V) const
{
	return (X != V.X) || (Y != V.Y) || (Z != V.Z) || (W != V.W);
}

FORCEINLINE bool FPlane::Equals(const FPlane& V, float Tolerance) const
{
	return (FMath::Abs(X - V.X) < Tolerance) && (FMath::Abs(Y - V.Y) < Tolerance) 
		&& (FMath::Abs(Z - V.Z) < Tolerance) && (FMath::Abs(W - V.W) < Tolerance);
}

FORCEINLINE float FPlane::operator|(const FPlane& V) const
{
	return X * V.X + Y * V.Y + Z * V.Z + W * V.W;
}

FORCEINLINE FPlane FPlane::operator+(const FPlane& V) const
{
	return FPlane(X + V.X, Y + V.Y, Z + V.Z, W + V.W);
}

FORCEINLINE FPlane FPlane::operator-(const FPlane& V) const
{
	return FPlane(X - V.X, Y - V.Y, Z - V.Z, W - V.W);
}

FORCEINLINE FPlane FPlane::operator/(float Scale) const
{
	const float RScale = 1.f / Scale;

	return FPlane(X * RScale, Y * RScale, Z * RScale, W * RScale);
}

FORCEINLINE FPlane FPlane::operator*(float Scale) const
{
	return FPlane(X * Scale, Y * Scale, Z * Scale, W * Scale);
}

FORCEINLINE FPlane FPlane::operator*(const FPlane& V)
{
	return FPlane(X * V.X, Y * V.Y, Z * V.Z, W * V.W);

}

FORCEINLINE FPlane FPlane::operator+=(const FPlane& V)
{
	X += V.X; Y += V.Y; Z += V.Z; W += V.W;

	return *this;
}

FORCEINLINE FPlane FPlane::operator-=(const FPlane& V)
{
	X -= V.X; Y -= V.Y; Z -= V.Z; W -= V.W;

	return *this;
}

FORCEINLINE FPlane FPlane::operator*=(float Scale)
{
	X *= Scale; Y *= Scale; Z *= Scale; W *= Scale;

	return *this;
}

FORCEINLINE FPlane FPlane::operator*=(const FPlane& V)
{
	X *= V.X; Y *= V.Y; Z *= V.Z; W *= V.W;

	return *this;
}

FORCEINLINE FPlane FPlane::operator/=(float V)
{
	const float RV = 1.f / V;

	X *= RV; Y *= RV; Z *= RV; W *= RV;

	return *this;
}