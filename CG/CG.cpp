// Este código pertence a um projeto pessoal,
// baseado no código aberto da Unreal Engine,
// com o intuito de aprendizado. Apenas as 
// estrutura básica das classes são semelhantes
// e as vezes iguais, já os corpos de métodos
// são implementações próprias do desenvolvedor
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