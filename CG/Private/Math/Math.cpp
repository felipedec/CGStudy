/*----------------------------------------------------------------------------
         Código baseado no código aberto da Unreal Engine
----------------------------------------------------------------------------*/

#pragma once

#include "CoreTypes.h"

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
         Color Global(s).
----------------------------------------------------------------------------*/

CORE_API const FColor32 FColor32::Blank(0x00000000);
CORE_API const FColor32 FColor32::Black(0x000000FF);
CORE_API const FColor32 FColor32::White(0xFFFFFFFF);
CORE_API const FColor32 FColor32::Blue(0x0000FFFF);
CORE_API const FColor32 FColor32::Red(0xFF0000FF);
CORE_API const FColor32 FColor32::Green(0x00FF00FF);
CORE_API const FColor32 FColor32::Cyan(0x00FFFFFF);
CORE_API const FColor32 FColor32::Grey(0xD3D3D3FF);
CORE_API const FColor32 FColor32::Magenta(0xFF00FFFF);
CORE_API const FColor32 FColor32::Yellow(0xFFFF00FF);

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
