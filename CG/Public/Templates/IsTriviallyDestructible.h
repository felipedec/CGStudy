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

namespace Engine_Private
{
	template <typename T, bool bIsTriviallyTriviallyDestructible = __is_enum(T)> struct TImpl : TConstBoolean<true> {};
	template <typename T> struct TImpl<T, false> : TConstBoolean<__has_trivial_destructor(T)> {};
}

template <typename T> struct TIsTriviallyDestructible : TConstBoolean<Engine_Private::TImpl<T>::Value> {};
