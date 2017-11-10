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
