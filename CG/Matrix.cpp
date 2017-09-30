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

#include "Matrix.h"

FMatrix FMatrix::Identy
(
	FVector4(1, 0, 0, 0),
	FVector4(0, 1, 0, 0),
	FVector4(0, 0, 1, 0),
	FVector4(0, 0, 0, 1)
);