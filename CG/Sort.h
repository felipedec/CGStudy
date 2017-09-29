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

#pragma warning(disable:4018)

#include "Core.h"

template<typename T>
using TCompareDelegate = bool(*)(const T&, const T&);

template<typename T>
using TSortDelegate = void(*)(T[], const SIZE_T, TCompareDelegate<T>);

class FSort
{
public:

	template<typename T>
	FORCEINLINE static void CocktailSort(T Array[], const SIZE_T Size, TCompareDelegate<T> Compare)
	{
		if (Array == nullptr || Size < 2)
		{
			return;
		}

		SIZE_T Bottom = 0;
		SIZE_T Top = Size - 1;
		bool bHasBeenSwapped = true;

		while (Bottom < Top && bHasBeenSwapped)
		{
			bHasBeenSwapped = false;

			for (SIZE_T Index = Bottom; Index < Top; Index++)
			{
				if (Compare(Array[Index + 1], Array[Index]))
				{
					Swap(&Array[Index + 1], &Array[Index]);
					bHasBeenSwapped = true;
				}
			}

			Top--;

			for (SIZE_T Index = Top; Index > Bottom; Index--)
			{
				if (Compare(Array[Index], Array[Index - 1]))
				{
					Swap(&Array[Index], &Array[Index - 1]);
					bHasBeenSwapped = true;
				}
			}

			Bottom++;
		}
	}

	template<typename T>
	FORCEINLINE static void SelectionSort(T Array[], const SIZE_T Size, TCompareDelegate<T> Compare)
	{
		if (Array == nullptr || Size < 2)
		{
			return;
		}

		for (SIZE_T Index = 0; Index < Size - 1; Index++)
		{
			SIZE_T LessIndex = Index;

			for (SIZE_T Index2 = Index + 1; Index2 < Size; Index2++)
			{
				if (Compare(Array[Index2], Array[LessIndex]))
				{
					LessIndex = Index2;
				}
			}

			if (Index != LessIndex)
			{
				Swap(&Array[Index], &Array[LessIndex]);
			}
		}
	}

	template<typename T>
	FORCEINLINE static void BubbleSort(T Array[], const SIZE_T Size, TCompareDelegate<T> Compare)
	{
		if (Array == nullptr || Size < 2)
		{
			return;
		}

		for (SIZE_T Index = Size - 1; Index > 0; Index--)
		{
			for (SIZE_T Index2 = 0; Index2 < Index; Index2++)
			{
				if (Compare(Array[Index2], Array[Index2 + 1]))
				{
					Swap(&Array[Index2], &Array[Index2 + 1]);
				}
			}
		}
	}

	template<typename T>
	FORCEINLINE static void InsertionSort(T Array[], const SIZE_T Size, TCompareDelegate<T> Compare)
	{
		if (Array == nullptr || Size < 2)
		{
			return;
		}

		for (SIZE_T Index = 1; Index < Size; Index++)
		{
			T Temp = Array[Index];
			SSIZE_T Index2 = Index - 1;

			while (Index2 >= 0 && Compare(Temp, Array[Index2]))
			{
				Array[Index2 + 1] = Array[Index2];
				Index2--;
			}
			Array[Index2 + 1] = Temp;
		}
	}	

	template<typename T>
	FORCEINLINE static void CombSort(T Array[], const SIZE_T Size, TCompareDelegate<T> Compare)
	{
		if (Array == nullptr || Size < 2)
		{
			return;
		}

		SIZE_T Gap = static_cast<SIZE_T>(Size / 1.3f);
		SIZE_T Index = 0;

		while (Gap > 0 && Index < Size)
		{
			Index = 0;

			while (Gap + Index < Size)
			{
				if (Compare(Array[Index + Gap], Array[Index]))
				{
					Swap(&Array[Index + Gap], &Array[Index]);
				}
				Index++;
			}
			Gap = static_cast<SIZE_T>(Gap / 1.3f);
		}
	}

	template<typename T>
	FORCEINLINE static void ShellSort(T Array[], const SIZE_T Size, TCompareDelegate<T> Compare)
	{
		if (Array == nullptr || Size < 2)
		{
			return;
		}

		bool bHasBeenSwapped = true;
		SIZE_T Gap = Size;

		while (bHasBeenSwapped || Gap > 1)
		{
			bHasBeenSwapped = false;

			Gap = (Gap + 1) / 2;

			for (SIZE_T Index = 0; Index < Size - Gap; Index++)
			{
				if (Compare(Array[Index + Gap], Array[Index]))
				{
					Swap(&Array[Index + Gap], &Array[Index]);
				}
			}
		}
	}

public:

	template<typename T>
	FORCEINLINE static void Swap(T* Lhs, T* Rhs)
	{
		T Temp = *Lhs;
		*Lhs = *Rhs;
		*Rhs = Temp;
	}
};
