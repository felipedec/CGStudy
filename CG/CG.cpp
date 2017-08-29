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
#include "Matrix2x2.h"
#include "Matrix3x3.h"
#include "Matrix4x4.h"

#include<ctime>


int main()
{
	FVector3 a, b, c, d;

	std::clock_t BeginClock = std::clock();

	for (int Index = 0; Index < 10E6; Index++)
	{
		FCurveUtility::GetPoint(a, b, c, d, 0.5f);
	}

	std::cout << (std::clock() - BeginClock) / CLOCKS_PER_SEC << std::endl;
	std::getchar();
	return 0;
}