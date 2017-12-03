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

namespace Engine_Private
{
	template <typename T, bool bIsTriviallyTriviallyDestructible = __is_enum(T)> struct TImpl : TConstBoolean<true> {};
	template <typename T> struct TImpl<T, false> : TConstBoolean<__has_trivial_destructor(T)> {};
}

template <typename T> struct TIsTriviallyDestructible : TConstBoolean<Engine_Private::TImpl<T>::Value> {};
