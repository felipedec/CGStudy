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

class FCurveUtility
{
public:

	/**
	 * Obtém um ponto em uma curva de Bezier.
	 *
	 * @param Lhs			Ponto de partida da curva.
	 * @param LhsTagent	Tangente do ponto de partida.
	 * @param Rhs			Ponto de chegada da curva.
	 * @param RhsTangent Tangente do ponto de chegada da curva.
	 * @param T				Índice da curva.
	 * @return O ponto da curva no índice T.
	 */
	template<typename TVector>
	FORCEINLINE static TVector GetPoint(const TVector& Lhs, const TVector& LhsTangent, const TVector& Rhs, const TVector& RhsTangent, const float T)
	{
		static_assert(TIsSame<FVector2, TVector>() || TIsSame<FVector3, TVector>(), "TVector must be FVector3 or FVector2.");

		float OneMinusT = (1 - T);

		return (Lhs * OneMinusT) + (LhsTangent * 3 * T * OneMinusT * OneMinusT) + (RhsTangent * 3 * T * T * OneMinusT) + (Rhs * OneMinusT * OneMinusT * OneMinusT);
	}

	/**
	 * Obtém um ponto em uma curva de Bezier.
	 *
	 * @param Destiantion Buffer para armazenar os pontos interpolados da curva.
	 * @param Size			Taamnho do buffer.
	 * @param Lhs			Ponto de partida da curva.
	 * @param LhsTagent	Tangente do ponto de partida.
	 * @param Rhs			Ponto de chegada da curva.
	 * @param RhsTangent Tangente do ponto de chegada da curva.
	 * @return O ponto da curva no índice T.
	 */
	template<typename TVector>
	FORCEINLINE static TVector GetPoints(TVector* Destination, uint32_t Size, const TVector& Lhs, const TVector& LhsTangent, const TVector& Rhs, const TVector& RhsTangent)
	{
		static_assert(TIsSame<FVector2, TVector>() || TIsSame<FVector3, TVector>(), "TVector must be FVector3 or FVector2.");
			
		for (uint32_t Index = 0; Index < Size; Index++)
		{
			Destination[Index] = GetPoint(Lhs, LhsTangent, Rhs, RhsTangent, static_cast<float>(Index) / (Size - 1));
		}
	}
};