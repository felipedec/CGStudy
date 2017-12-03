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

#include "Templates/TypeTraits.h"
#include "Templates/IsTriviallyCopyConstructible.h"

template <typename T, typename Arg>
struct TIsBitwiseConstructible : TConstBoolean<false>
{
	static_assert(
		!TIsReference<T>::Value &&
		!TIsReference<Arg>::Value,
		"TIsBitwiseConstructible is not designed to accept reference types");

	static_assert(
		TIsSame<T, REMOVE_CV(T)>::Value &&
		TIsSame<Arg, REMOVE_CV(Arg)>::Value,
		"TIsBitwiseConstructible is not designed to accept qualified types");
};

/*----------------------------------------------------------------------------
			Specialization.
----------------------------------------------------------------------------*/

template <typename T> struct TIsBitwiseConstructible<T, T> : TIsTriviallyCopyConstructible<T> {};
template <typename T, typename U> struct TIsBitwiseConstructible<const T, U> : TIsBitwiseConstructible<T, U> {};
template <typename T> struct TIsBitwiseConstructible<const T*, T*> : TConstBoolean<true> {};

template <> struct TIsBitwiseConstructible<uint8, int8> : TConstBoolean<true> {};
template <> struct TIsBitwiseConstructible<int8, uint8> : TConstBoolean<true> {};
template <> struct TIsBitwiseConstructible<uint16, int16> : TConstBoolean<true> {};
template <> struct TIsBitwiseConstructible<int16, uint16> : TConstBoolean<true> {};
template <> struct TIsBitwiseConstructible<uint32, int32> : TConstBoolean<true> {};
template <> struct TIsBitwiseConstructible<int32, uint32> : TConstBoolean<true> {};
template <> struct TIsBitwiseConstructible<uint64, int64> : TConstBoolean<true> {};
template <> struct TIsBitwiseConstructible<int64, uint64> : TConstBoolean<true> {};
