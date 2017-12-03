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

#include "Templates/IsPODType.h"
#include "Templates/TypeTraits.h"

template <typename T> struct TIsTriviallyCopyConstructible : TConstBoolean<TIsPODType<T>::Value || __has_trivial_copy(T)> {};