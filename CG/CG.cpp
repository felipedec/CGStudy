// Este código pertence a um projeto pessoal,
// baseado no código aberto da Unreal Engine,
// com o intuito de aprendizado. Apenas as 
// estrutura básica das classes são semelhantes
// e as vezes iguais, já os corpos de métodos
// são implementações próprias do desenvolvedor
// deste projeto.
//
// Saiba mais:
// https://github.com/felipedec/LeafEngine

#include "CoreTypes.h"

#include <iomanip>


void PrintMatrix(const FMatrix& M)
{
	for (uint8_t Column = 0; Column < 4; Column++)
	{
		for (uint8_t Row = 0; Row < 4; Row++)
		{
			std::cout << std::setfill(' ') << std::setw(16) << M.M[Column][Row];
		}
		std::cout <<  std::endl;
	}
	std::cout << std::endl;
}

void A(int b, int c, double a, FVector v)
{

}

class Class
{
public:

	static void StaticClass(int a)
	{

	}

	void A(int b, int c, double a, FVector v) const
	{

	}
};

struct FScene
{
	FVector ObjPosition;
	FVector ObjScale;
	FVector ObjRotation;

	FVector CameraPosition;
	FVector CameraRotation;
};

#define SCREEN_RESOLUTION 512

static int8 Buffer[SCREEN_RESOLUTION << 1];

#include <ctime>
#include <bitset>

int main()
{
	std::cout << TIsStruct<FMatrix>::Value << std::endl;
	std::cout << 180 * FMath::Deg2Rad << std::endl;

	std::cout << FMath::Sine(FMath::Deg2Rad * 360) << std::endl;
	std::cout << FMath::Sine(FMath::Deg2Rad * 270) << std::endl;
	std::cout << FMath::Sine(FMath::Deg2Rad * 180) << std::endl;
	std::cout << FMath::Sine(FMath::Deg2Rad * 90) << std::endl;
	std::cout << FMath::Sine(FMath::Deg2Rad * 45) << std::endl;
	std::cout << FMath::Sine(FMath::Deg2Rad * 30) << std::endl;
	std::cout << FMath::Sine(FMath::Deg2Rad * 0) << std::endl;

 	int64 c = 0;
	int64 Clock = clock();

	//constexpr int64 t = 10000;
	//float Result;

	//for(int j = 0; j < t; j++)
	//for (int64 i = 0; i < t; i++)
	//{
	//	Result = 1 / FMath::InvSqrt(6620329);

	//	c++;
	//}

	//std::cout << ((double)(clock() - Clock)) / CLOCKS_PER_SEC << std::endl;
	//std::cout << Result << std::endl;


	//Clock = clock();

	//for (int j = 0; j < t; j++)
	//for (int64 i = 0; i < t; i++)
	//{
	//	Result = sqrt14(6620329);
	//	c++;
	//}

	//std::cout << ((double)(clock() - Clock)) / CLOCKS_PER_SEC << std::endl;
	//std::cout << Result << std::endl;
	//std::cout << c << std::endl;


	std::getchar();

}