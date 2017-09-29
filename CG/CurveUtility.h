/*----------------------------------------------------------------------------
			Este c�digo pertence a um projeto pessoal,
			baseado no c�digo aberto da Unreal Engine,
			com o intuito de aprendizado. Apenas as
			estrutura b�sica das classes s�o semelhantes
			e as vezes iguais, j� os corpos de m�todos
			s�o implementa��es pr�prias do desenvolvedor
			deste projeto.
			
			Saiba mais:
			https://github.com/felipedec/CGStudy
----------------------------------------------------------------------------*/

#pragma once

#include "CoreFwd.h"

class FCurveUtility
{
public:

	/**
	 * Obt�m um ponto em uma curva de Bezier.
	 *	
	 * @param Lhs			Ponto de partida da curva.
	 * @param LhsTagent	Tangente do ponto de partida.
	 * @param Rhs			Ponto de chegada da curva.
	 * @param RhsTangent Tangente do ponto de chegada da curva.
	 * @param T				�ndice da curva.
	 * @return O ponto da curva no �ndice T.
	 */
	template<typename TVector>
	FORCEINLINE static TVector GetPoint(const TVector& Lhs, const TVector& LhsTangent, const TVector& Rhs, const TVector& RhsTangent, const float T)
	{
		static_assert(TIsSame<FVector2, TVector>() || TIsSame<FVector, TVector>(), "TVector must be FVector or FVector2.");

		const float OneMinusT = (1 - T);

		return (Lhs * OneMinusT) + (LhsTangent * 3 * T * OneMinusT * OneMinusT) + (RhsTangent * 3 * T * T * OneMinusT) + (Rhs * OneMinusT * OneMinusT * OneMinusT);
	}

	/**
	 * Obt�m um ponto em uma curva de Bezier.
	 *
	 * @param Dest			Buffer para armazenar os pontos interpolados da curva.
	 * @param Size			Taamnho do buffer.
	 * @param Lhs			Ponto de partida da curva.
	 * @param LhsTagent	Tangente do ponto de partida.
	 * @param Rhs			Ponto de chegada da curva.
	 * @param RhsTangent Tangente do ponto de chegada da curva.
	 * @return O ponto da curva no �ndice T.
	 */
	template<typename TVector>
	FORCEINLINE static TVector GetPoints(TVector* Dest, const SIZE_T Size, const TVector& Lhs, const TVector& LhsTangent, const TVector& Rhs, const TVector& RhsTangent)
	{
		static_assert(TIsSame<FVector2, TVector>() || TIsSame<FVector, TVector>(), "TVector must be FVector or FVector2.");
			
		for (uint32 Index = 0; Index < Size; Index++)
		{
			Dest[Index] = GetPoint(Lhs, LhsTangent, Rhs, RhsTangent, static_cast<float>(Index) / (Size - 1));
		}
	}
};