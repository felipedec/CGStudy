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

#if defined(USE_DIRECTX_MATH)
#include "Math/DirectXMath.h"
#endif

MS_ALIGN(16) struct FMatrix
{
public:
	
	union 
	{
		struct
		{
			/** Componentes da primeira linha */
			float M00, M01, M02, M03;

			/** Componentes da segunda linha */
			float M10, M11, M12, M13;

			/** Componentes da terceira linha */
			float M20, M21, M22, M23;

			/** Componentes da quarta linha */
			float M30, M31, M32, M33;
		};

		struct
		{
			float M[4][4];
		};
	};

public:

	/** Matr�z identidade */
	CORE_API static const FMatrix Identy;

public:

	/** Construtor sem inicializa��o dos componentes */
	FORCEINLINE FMatrix() = default;

	/** Construtor passando cada linha por planos */
	FORCEINLINE FMatrix(const FPlane& X, const FPlane& Y, const FPlane& Z, const FPlane& W);

public:

	/**
	 * Obtem o resultado da multiplica��o dessa matr�z com outra.
	 *
	 * @param Other Outra matr�z da opera��o.
	 * @return Resultado da multiplica��o entre as matr�zes.
	 */
	FORCEINLINE FMatrix operator*(const FMatrix& Other) const;

	/**
	* Obtem o resultado da multiplica��o dessa matr�z com outra e armazena o resultado nesta matrix.
	*
	* @param Other Outra matr�z da opera��o.
	*/
	FORCEINLINE void operator*=(const FMatrix& Other) const;

	/**
	 * Obtem uma matr�z sendo cada componente a soma dos respectivos componentes desta matr�z e a outra.
	 *
	 * @param Other Outra matr�z.
	 * @return Matr�z com a soma dos componentes.
	 */
	FORCEINLINE FMatrix operator+(const FMatrix& Other) const;

	/**
	 * Obtem uma matr�z sendo cada componente a subtra��o dos respectivos componentes desta matr�z e a outra.
	 *
	 * @param Other Outra matr�z.
	 * @return Matr�z com a subtra��o dos componentes.
	 */
	FORCEINLINE FMatrix operator-(const FMatrix& Other) const;

	/**
	 * Obtem o resultado do produto da matr�z com um vetor de tr�s componente.
	 *
	 * @param V Vetor.
	 * @return O resultado do produto da matr�z com um vetor.
	 */
	FORCEINLINE FVector4 operator*(const FVector& V) const;

	/**
	* Obtem o resultado do produto da matr�z com um vetor de quatro componente.
	*
	* @param V Vetor.
	* @return O resultado do produto da matr�z com um vetor.
	*/
	FORCEINLINE FVector4 operator*(const FVector4& V) const;

public:

	/**
	* Obt�m uma c�pia da matr�z transposta.
	*
	* @return Retorna uma c�pia da matr�z transposta.
	*/
	FORCEINLINE FMatrix GetTransposed() const;

	/**
	 * Obt�m uma c�pia da matr�z invertida.
	 *
	 * @return Retorna uma c�pia da matr�z invertida.
	 */
	FORCEINLINE FMatrix Inverse() const;

public: 
	
	/** Obtem o resultado da transform��o entre esta matr�z e o vetor */
	FORCEINLINE FVector4 TransformFVector4(const FVector4& Vector) const;

	/** Obtem o resultado da transform��o entre esta matr�z e a a posi��o */
	FORCEINLINE FVector4 TransformPosition(const FVector& Vector) const;

} GCC_ALIGN(16);

/* ---------------- Inline functions ---------------- */

#include "Vector.h"
#include "Vector4.h"
#include "Plane.h"

FORCEINLINE FMatrix::FMatrix(const FPlane& InX, const FPlane& InY, const FPlane& InZ, const FPlane& InW)
{
	M[0][0] = InX.X;
	M[1][0] = InY.X;
	M[2][0] = InZ.X;
	M[3][0] = InW.X;

	M[0][1] = InX.Y;
	M[1][1] = InY.Y;  
	M[2][1] = InZ.Y;  
	M[3][1] = InW.Y;  

	M[0][2] = InX.Z;
	M[1][2] = InY.Z;
	M[2][2] = InZ.Z;
	M[3][2] = InW.Z;

	M[0][3] = InX.W;
	M[1][3] = InY.W;
	M[2][3] = InZ.W;
	M[3][3] = InW.W;
}

FORCEINLINE FMatrix FMatrix::operator*(const FMatrix& Other) const
{
	FMatrix Result;
	Engine_Private::VectorMatrixMultiply(&Result, *this, Other);
	
	return Result;
}

FORCEINLINE void FMatrix::operator*=(const FMatrix& Other) const
{		
	Engine_Private::VectorMatrixMultiply((FMatrix*)this, *this, Other);
}

FORCEINLINE FMatrix FMatrix::operator+(const FMatrix& Other) const
{
	FMatrix Result;

	for (uint32 Column = 0; Column < 4; Column++)
	{
		for (uint32 Row = 0; Row < 4; Row++)
		{
			Result.M[Column][Row] = M[Column][Row] + Other.M[Column][Row];
		}
	}
}

FORCEINLINE FMatrix FMatrix::operator-(const FMatrix& Other) const
{
	FMatrix Result;

	for (uint32 Column = 0; Column < 4; Column++)
	{
		for (uint32 Row = 0; Row < 4; Row++)
		{
			Result.M[Column][Row] = M[Column][Row] - Other.M[Column][Row];
		}
	}

	return Result;
}

FORCEINLINE FVector4 FMatrix::operator*(const FVector& V) const
{
	return TransformPosition(V);
}

FORCEINLINE FVector4 FMatrix::operator*(const FVector4& V) const
{
	return TransformFVector4(V);
}

FORCEINLINE FMatrix FMatrix::GetTransposed() const
{
	FMatrix	Result;

	Result.M[0][0] = M[0][0];
	Result.M[0][1] = M[1][0];
	Result.M[0][2] = M[2][0];
	Result.M[0][3] = M[3][0];

	Result.M[1][0] = M[0][1];
	Result.M[1][1] = M[1][1];
	Result.M[1][2] = M[2][1];
	Result.M[1][3] = M[3][1];

	Result.M[2][0] = M[0][2];
	Result.M[2][1] = M[1][2];
	Result.M[2][2] = M[2][2];
	Result.M[2][3] = M[3][2];

	Result.M[3][0] = M[0][3];
	Result.M[3][1] = M[1][3];
	Result.M[3][2] = M[2][3];
	Result.M[3][3] = M[3][3];

	return Result;
}

FORCEINLINE FMatrix FMatrix::Inverse() const
{
	FMatrix Result;
	Engine_Private::VectorMatrixInverse(&Result, *this);

	return Result;
}

FORCEINLINE FVector4 FMatrix::TransformFVector4(const FVector4& Vector) const
{
	FVector4 Result;
	Engine_Private::VectorMatrixTransformFVector4(&Result, *this, Vector);

	return Result;
}

FORCEINLINE FVector4 FMatrix::TransformPosition(const FVector& Vector) const
{
	return TransformFVector4(FVector4(Vector.X, Vector.Y, Vector.Z, 1.0f));
}
