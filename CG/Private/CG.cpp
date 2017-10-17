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

/*----------------------------------------------------------------------------
			Macros.
----------------------------------------------------------------------------*/

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 32

/*----------------------------------------------------------------------------
			Globals.
----------------------------------------------------------------------------*/

CHAR8 GFrameBuffer[SCREEN_HEIGHT][SCREEN_WIDTH];
FVector2 GScreenSize(SCREEN_HEIGHT, SCREEN_WIDTH);

/*----------------------------------------------------------------------------
			Metodos.
----------------------------------------------------------------------------*/

void DrawPixel(const FVector2& NormalizedScreenPosition)
{
	if (NormalizedScreenPosition.X < 0 || NormalizedScreenPosition.Y < 0
		|| NormalizedScreenPosition.X > 1 || NormalizedScreenPosition.Y > 1)
	{
		return;
	}

	int32 X = static_cast<int32>(NormalizedScreenPosition.X * SCREEN_WIDTH);
	int32 Y = static_cast<int32>(NormalizedScreenPosition.Y * SCREEN_HEIGHT);

	GFrameBuffer[Y][X] = 178;
}

FVector2 NormalizeScreenPosition(FVector Position)
{
	FVector2 ScreenPosition = Position;
	ScreenPosition += GScreenSize / 2;
	ScreenPosition.X /= GScreenSize.X;
	ScreenPosition.Y /= GScreenSize.Y;
	
	return ScreenPosition;
}

FORCEINLINE void ClearBuffer()
{
	std::memset(GFrameBuffer, 176, SCREEN_WIDTH * SCREEN_HEIGHT);
}

FORCEINLINE void DrawBuffer()
{
	for (int32 Index = 0; Index < SCREEN_HEIGHT; Index++)
	{
		GFrameBuffer[Index][SCREEN_WIDTH - 1] = '\0';
		std::cout << GFrameBuffer[Index] << std::endl;
	}
}

/*----------------------------------------------------------------------------
			Objeto 3D.
----------------------------------------------------------------------------*/

#define SIZE 8

const FVector GVertices[] =
{
	FVector(-SIZE, SIZE, -SIZE),
	FVector(SIZE, SIZE, -SIZE),
	FVector(SIZE, -SIZE, -SIZE),
	FVector(-SIZE, -SIZE, -SIZE),

	FVector(-SIZE, SIZE, SIZE),
	FVector(SIZE, SIZE, SIZE),
	FVector(SIZE, -SIZE, SIZE),
	FVector(-SIZE, -SIZE, SIZE),
};

/*----------------------------------------------------------------------------
			Main.
----------------------------------------------------------------------------*/

#include<ctime>
#include <stdlib.h>

int main()
{
	while (true)
	{
		clock_t LastUpdate = clock();

		float Time = clock() / CLOCKS_PER_SEC;

		FMatrix ViewMatrix = FQuaternion(0, 20, 0) * FTranslationMatrix::Make(FVector(0, 0, 0));
		FMatrix ObjectMatrix = FQuaternion(Time * 15, 0, 0) * FTranslationMatrix::Make(FVector(0, 0, -10));
		FMatrix ProjectionMatrix = FPerspectiveMatrix(FMath::Pi / 4, SCREEN_WIDTH, SCREEN_HEIGHT, 0, 1000);

		system("cls");
		ClearBuffer();

		FMatrix Matrix = ObjectMatrix * ViewMatrix * ProjectionMatrix;

		for (int32 Index = 0; Index < TExtent<decltype(GVertices)>::Value; Index++)
		{
			FVector Position = Matrix.TransformPosition(GVertices[Index]);
			FVector2 ScreenPosition = NormalizeScreenPosition(Position);
			DrawPixel(ScreenPosition);
		}

		DrawBuffer();

		while ((clock() - LastUpdate) / CLOCKS_PER_SEC < 0.25f)
		{

		}
	}


	std::getchar();
}