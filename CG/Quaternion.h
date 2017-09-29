/*----------------------------------------------------------------------------
			Este c�digo pertence a um projeto pessoal,
			baseado no c�digo aberto da Unreal Engine,
			com o intuito de aprendizado. Apenas as
			estrutura b�sica das classes s�o semelhantes
			e as vezes iguais, j� os corpos de m�todos
			s�o implementa��es pr�prias do desenvolvedor
			deste projeto.
			
			Saiba mais:
			https://github.com/felipedec/CGStudy
----------------------------------------------------------------------------*/

#pragma once

#include "Core.h"

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
	static CORE_API const FQuaternion Identity;

public:

	/**
	 * Construtor, espec�ficando cada componente do quaternion.
	 *
	 * @param InX Componente X do quaternion.
	 * @param InY Componente Y do quaternion.
	 * @param InZ Componente Z do quaternion.
	 * @param InW Componente W do quaternion.
	 */
	FORCEINLINE FQuaternion(const float InX, const float InY, const float InZ, const float InW);

} GCC_ALIGN(16);

FORCEINLINE FQuaternion::FQuaternion(const float InX, const float InY, const float InZ, const float InW) :
	X(InX),
	Y(InY),
	Z(InZ),
	W(InW)
{
}

