/*----------------------------------------------------------------------------
			Este código pertence a um projeto pessoal,
			baseado no código aberto da Unreal Engine,
			com o intuito de aprendizado. Apenas as
			estrutura básica das classes são semelhantes
			e as vezes iguais, já os corpos de métodos
			são implementações próprias do desenvolvedor
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

	/** Quaternion Identidade, corresponde a "sem rotação" */
	static CORE_API const FQuaternion Identity;

public:

	/**
	 * Construtor, específicando cada componente do quaternion.
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

