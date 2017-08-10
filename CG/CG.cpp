// Este c�digo pertence a um projeto pessoal,
// baseado no c�digo aberto da Unreal Engine,
// com o intuito de aprendizado. Apenas as 
// estrutura b�sica das classes s�o semelhantes
// e as vezes iguais, j� os corpos de m�todos
// s�o implementa��es pr�prias do desenvolvedor
// deste projeto.
//
// Saiba mais:
// https://github.com/felipedec/CGStudy

#include "Core.h"	
#include "Vector2.h"
#include "Vector3.h"
#include "Vector4.h"


int main()
{
	FVector2 Vector(30, 50);

	std::cout << Vector[1] << std::endl;
	std::cout << FVector3::Distance(FVector3(0, 1, 0), FVector3(1, 0, 1)) << std::endl;

	std::getchar();

	return 0;
}