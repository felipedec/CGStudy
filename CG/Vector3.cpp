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

#include "Vector.h"

const FVector FVector::Zero(0, 0, 0);
const FVector FVector::One(1, 1, 1);
const FVector FVector::Right(1, 0, 0);
const FVector FVector::Left(-1, 0, 0);
const FVector FVector::Up(0, 1, 0);
const FVector FVector::Down(0, -1, 0);
const FVector FVector::Forward(0, 0, 1);
const FVector FVector::Back(0, 0, -1);
