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

#include "CoreTypes.h"

static float Sign(float a)
{
	if (a > 0.0f) return 1.0f;
	if (a < 0.0f) return -1.0f;
	return 0.0f;
}

class FClipProjectionMatrix : public FMatrix
{
public:

	FClipProjectionMatrix(const FMatrix& SrcProjMat, const FPlane& Plane) :
		FMatrix(SrcProjMat)
	{
		FPlane CornerPlane
		(
			Sign(Plane.X) / SrcProjMat.M00,
			Sign(Plane.Y) / SrcProjMat.M11,
			1.0f,
			-(1.0f - SrcProjMat.M22) / SrcProjMat.M32
		);
		FPlane ProjPlane(Plane * (1.0f / (Plane | CornerPlane)));

		M[0][2] = ProjPlane.X;
		M[1][2] = ProjPlane.Y;
		M[2][2] = ProjPlane.Z;
		M[3][2] = -ProjPlane.W;
	}

public:

	/** F�brica de matr�zes */
	static CORE_API FMatrix Make(const FMatrix& SrcProjMat, const FPlane& Plane)
	{
		return FClipProjectionMatrix(SrcProjMat, Plane);
	}
};