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

#include "CoreTypes.h"
#include "Templates/IsPODType.h"

/*----------------------------------------------------------------------------
			FQuaternion Global(s).
----------------------------------------------------------------------------*/

CORE_API const FQuaternion FQuaternion::Identity(0, 0, 0, 1);

/*----------------------------------------------------------------------------
			FVector2 Global(s).
----------------------------------------------------------------------------*/

CORE_API const FVector2 FVector2::Zero(0, 0);
CORE_API const FVector2 FVector2::One(1, 1);
CORE_API const FVector2 FVector2::Right(1, 0);
CORE_API const FVector2 FVector2::Left(-1, 0);
CORE_API const FVector2 FVector2::Up(0, 1);
CORE_API const FVector2 FVector2::Down(0, -1);

/*----------------------------------------------------------------------------
			FVector4 Global(s).
----------------------------------------------------------------------------*/

CORE_API const FVector4 FVector4::Zero(0, 0, 0, 0);
CORE_API const FVector4 FVector4::One(1, 1, 1, 1);

/*----------------------------------------------------------------------------
			FVector Global(s).
----------------------------------------------------------------------------*/

CORE_API const FVector FVector::Zero(0, 0, 0);
CORE_API const FVector FVector::One(1, 1, 1);
CORE_API const FVector FVector::Right(1, 0, 0);
CORE_API const FVector FVector::Left(-1, 0, 0);
CORE_API const FVector FVector::Up(0, 1, 0);
CORE_API const FVector FVector::Down(0, -1, 0);
CORE_API const FVector FVector::Forward(0, 0, 1);
CORE_API const FVector FVector::Back(0, 0, -1);

/*----------------------------------------------------------------------------
			FMatrix Global(s).
----------------------------------------------------------------------------*/

CORE_API const FMatrix FMatrix::Identy
(
	FPlane(1, 0, 0, 0),
	FPlane(0, 1, 0, 0),
	FPlane(0, 0, 1, 0),
	FPlane(0, 0, 0, 1)
);

/*----------------------------------------------------------------------------
			TISPODType Specialization.
----------------------------------------------------------------------------*/

template <> struct TIsPODType<FMatrix> : TConstBoolean<true> {};
template <> struct TIsPODType<FPlane> : TConstBoolean<true> {};
template <> struct TIsPODType<FQuaternion> : TConstBoolean<true> {};
template <> struct TIsPODType<FVector> : TConstBoolean<true> {};
template <> struct TIsPODType<FVector2> : TConstBoolean<true> {};
template <> struct TIsPODType<FVector4> : TConstBoolean<true> {};
template <> struct TIsPODType<FColor32> : TConstBoolean<true> {};
