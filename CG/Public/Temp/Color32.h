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

union FColor32
{
public:

	struct
	{
		int8 R, G, B, A;
	};

	int8 Components[4];

	uint32 Int32;

public:

	FORCEINLINE FColor32() = default;

	FORCEINLINE FColor32(const uint32 InInt32) :
		Int32(InInt32)
	{

	}

	FORCEINLINE FColor32(const uint8 InR, const uint8 InG, const uint8 InB, const uint8 InA) :
		R(InR), G(InG), B(InB), A(InA)
	{

	}

};
