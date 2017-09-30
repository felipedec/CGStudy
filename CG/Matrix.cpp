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

#include "Matrix.h"

FMatrix FMatrix::Identy
(
	FVector4(1, 0, 0, 0),
	FVector4(0, 1, 0, 0),
	FVector4(0, 0, 1, 0),
	FVector4(0, 0, 0, 1)
);