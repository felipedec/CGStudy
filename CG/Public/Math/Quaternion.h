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


MS_ALIGN(16) struct FQuaternion
{
public:

   union
   {
      struct
      {
         /** Componente X do quaternion. */
         float X;

         /** Componente Y do quaternion. */
         float Y;

         /** Componente Z do quaternion. */
         float Z;

         /** Componente W do quaternion. */
         float W;
      };

      struct
      {
         float Components[4];
      };
   };

public:

   /** Quaternion Identidade, corresponde a "sem rota��o" */
   CORE_API static const FQuaternion Identity;

public:

   FORCEINLINE FQuaternion();

   /**
    * Construtor, espec�ficando cada componente do quaternion.
    *
    * @param InX Componente X do quaternion.
    * @param InY Componente Y do quaternion.
    * @param InZ Componente Z do quaternion.
    * @param InW Componente W do quaternion.
    */
   FORCEINLINE FQuaternion(const float InX, const float InY, const float InZ, const float InW);

   /**
    * Construtor de copia.
    *
    * @param Q Quaternion a ser copiado.
    */
   FORCEINLINE FQuaternion(const FQuaternion& Q);

   /**
    * Cria um Quaternion a partir de um matrix de rota��o.
    *
    * @param M A matrix de ref�rencia.
    */
   explicit FQuaternion(const FMatrix& M);

   /**
    * Cria um quaternion a partir de uma rota��o em um eixo.
    *
    * @param Axis Um vetor normalizado.
    * @param Angle Angulo da rota��o.
    */
   FORCEINLINE FQuaternion(const FVector& Axis, const float AngleRad);

   /**
    * Cria um quaternion a partir de uma rota��o em um eixo.
    *
    * @param Axis Um vetor normalizado.
    * @param Angle Angulo da rota��o.
    */
   FORCEINLINE FQuaternion(const float Pitch, const float Yaw, const float Roll);

public:

   /**
    * Compara se dois Quaternion s�o iguais.
    *
    * @param Q				O outro Quaternion.
    * @param Tolerance	Toler�ncia da compara��o.
    * @return Se os elementos forem suficientemente iguais retorna verdadeiro, caso contr�rio falso.
    */
   FORCEINLINE bool Equals(const FQuaternion& Q, float Tolerance = FMath::KindaSmallNumber) const;

   /**
    * Verifica se este Quaternion � um quaternion identidade.
    *
    * @param Tolerance Toler�ncia da compara��o.
    * @return Retorna verdadeiro se for identidade, caso contr�rio retorna falso.
    */
   FORCEINLINE bool IsIdentity(float Tolerance = FMath::SmallNumber) const;

public:

   /**
    * Obt�m o resultado da multiplica��o entre dois Quaternion.
    *
    * @param Q O Outro Quaternion.
    * @return Resultado da multiplica��o.
    */
   FORCEINLINE FQuaternion operator*(const FQuaternion& Q) const;

   /**
    * Aplica uma multiplica��o neste Quaternion por outro.
    *
    * @param Q O Outro Quaternion.
    * @return Uma copia deste Quaternion ap�s a multiplica��o.
    */
   FORCEINLINE FQuaternion operator*=(const FQuaternion& Q);

   /**
    * Obt�m o resultado da multiplica��o por um vetor.
    *
    * @param V O vetor.
    * @return Resultado da multiplica��o.
    */
   FVector operator*(const FVector& V) const;

   /**
    * Obt�m o resultado da multiplica��o por uma matr�x.
    *
    * @param M A Matr�x.
    * @return Resultado da multiplica��o.
    */
   FMatrix operator*(const FMatrix& M) const;

   FORCEINLINE FQuaternion operator*=(const float Scale);

   FORCEINLINE FQuaternion operator*(const float Scale) const;

   FORCEINLINE FQuaternion operator/=(const float Scale);

   FORCEINLINE FQuaternion operator/(const float Scale) const;

   bool operator==(const FQuaternion& Q) const;

   bool operator!=(const FQuaternion& Q) const;

   float operator|(const FQuaternion& Q) const;

public:

   FORCEINLINE FQuaternion FQuaternion::Inverse() const;

} GCC_ALIGN(16);

/* ---------------- Inline functions ---------------- */

#include "Math/Vector.h"
#include "Math/Vector4.h"
#include "Math/Matrix.h"

FORCEINLINE FQuaternion::FQuaternion()
{
}

FORCEINLINE FQuaternion::FQuaternion(const float InX, const float InY, const float InZ, const float InW) :
   X(InX),
   Y(InY),
   Z(InZ),
   W(InW)
{
}

FORCEINLINE FQuaternion::FQuaternion(const FQuaternion & Q) :
   X(Q.X),
   Y(Q.Y),
   Z(Q.Z),
   W(Q.W)
{
}

FORCEINLINE FQuaternion::FQuaternion(const FMatrix& M)
{
   Engine_Private::RotationMatrix2Quaternion(this, M);
}

FORCEINLINE FQuaternion::FQuaternion(const FVector& Axis, const float AngleRad)
{
   Engine_Private::QuaternionRotationAxis(this, Axis, AngleRad);
}

FORCEINLINE FQuaternion::FQuaternion(const float Pitch, const float Yaw, const float Roll)
{
   Engine_Private::QuaternionRotationEulerVector(this, FVector(Pitch, Yaw, Roll) * FMath::Deg2Rad);
}

FORCEINLINE bool FQuaternion::Equals(const FQuaternion & Q, float Tolerance) const
{
   return FMath::Abs(X - Q.X) <= Tolerance && FMath::Abs(Y - Q.Y) <= Tolerance
      && FMath::Abs(Z - Q.Z) <= Tolerance && FMath::Abs(W - Q.W) <= Tolerance;
}

FORCEINLINE bool FQuaternion::IsIdentity(float Tolerance) const
{
   return Equals(Identity, Tolerance);
}

FORCEINLINE FQuaternion FQuaternion::operator*(const FQuaternion& Q) const
{
   FQuaternion Result;

   Engine_Private::QuaternionMultiply(&Result, *this, Q);

   return Result;
}

FORCEINLINE FVector FQuaternion::operator*(const FVector& V) const
{
   FVector Result;

   Engine_Private::QuaternionTransformFVector(&Result, *this, V);

   return Result;
}

FORCEINLINE FMatrix FQuaternion::operator*(const FMatrix& M) const
{
   FMatrix RotationMatrix;

   Engine_Private::Quaternion2RotationMatrix(&RotationMatrix, *this);

   return RotationMatrix * M;
}

inline FQuaternion FQuaternion::operator*=(const FQuaternion & Q)
{
   return *this = *this * Q;
}

FORCEINLINE FQuaternion FQuaternion::operator*=(const float Scale)
{
   X *= Scale;
   Y *= Scale;
   Z *= Scale;
   W *= Scale;

   return *this;
}

FORCEINLINE FQuaternion FQuaternion::operator*(const float Scale) const
{
   FQuaternion Result = *this;

   Result.X *= Scale;
   Result.Y *= Scale;
   Result.Z *= Scale;
   Result.W *= Scale;

   return Result;
}

FORCEINLINE FQuaternion FQuaternion::operator/=(const float Scale)
{
   X /= Scale;
   Y /= Scale;
   Z /= Scale;
   W /= Scale;

   return *this;
}

FORCEINLINE FQuaternion FQuaternion::operator/(const float Scale) const
{
   FQuaternion Result = *this;

   Result.X /= Scale;
   Result.Y /= Scale;
   Result.Z /= Scale;
   Result.W /= Scale;

   return Result;
}

FORCEINLINE bool FQuaternion::operator==(const FQuaternion& Q) const
{
   return X == Q.X && Y == Q.Y && Z == Q.Z && W == Q.W;
}

FORCEINLINE bool FQuaternion::operator!=(const FQuaternion& Q) const
{
   return X != Q.X || Y != Q.Y || Z != Q.Z || W != Q.W;
}

FORCEINLINE float FQuaternion::operator|(const FQuaternion& Q) const
{
   return Engine_Private::QuaternionDot(*this, Q);
}

FORCEINLINE FQuaternion FQuaternion::Inverse() const
{
   return FQuaternion(-X, -Z, -Y, W);
}

/* ---------------- Global operators functions ---------------- */

FORCEINLINE FMatrix operator*(const FMatrix& M, const FQuaternion& Quaternion)
{
   FMatrix RotationMatrix;

   Engine_Private::Quaternion2RotationMatrix(&RotationMatrix, Quaternion);

   return M * RotationMatrix;
}