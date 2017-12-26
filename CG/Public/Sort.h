// Código baseado no código aberto da Unreal Engine

#pragma once
#pragma warning(push)
#pragma warning(disable:4018)

#include "Core.h"

template<typename T>
using TCompareDelegate = bool(*)(const T&, const T&);

template<typename T>
using TSortDelegate = void(*)(T[], const uint32, TCompareDelegate<T>);

class FSort
{
public:

	template<typename T>
	FORCEINLINE static void CocktailSort(T Array[], const uint32 Size, TCompareDelegate<T> Compare)
	{
		if (Array == nullptr || Size < 2)
		{
			return;
		}

		uint32 Bottom = 0;
		uint32 Top = Size - 1;
		bool bHasBeenSwapped = true;

		while (Bottom < Top && bHasBeenSwapped)
		{
			bHasBeenSwapped = false;

			for (uint32 Index = Bottom; Index < Top; Index++)
			{
				if (Compare(Array[Index + 1], Array[Index]))
				{
					Swap(&Array[Index + 1], &Array[Index]);
					bHasBeenSwapped = true;
				}
			}

			Top--;

			for (uint32 Index = Top; Index > Bottom; Index--)
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
	FORCEINLINE static void SelectionSort(T Array[], const uint32 Size, TCompareDelegate<T> Compare)
	{
		if (Array == nullptr || Size < 2)
		{
			return;
		}

		for (uint32 Index = 0; Index < Size - 1; Index++)
		{
			uint32 LessIndex = Index;

			for (uint32 Index2 = Index + 1; Index2 < Size; Index2++)
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
	FORCEINLINE static void BubbleSort(T Array[], const uint32 Size, TCompareDelegate<T> Compare)
	{
		if (Array == nullptr || Size < 2)
		{
			return;
		}

		for (uint32 Index = Size - 1; Index > 0; Index--)
		{
			for (uint32 Index2 = 0; Index2 < Index; Index2++)
			{
				if (Compare(Array[Index2], Array[Index2 + 1]))
				{
					Swap(&Array[Index2], &Array[Index2 + 1]);
				}
			}
		}
	}

	template<typename T>
	FORCEINLINE static void InsertionSort(T Array[], const uint32 Size, TCompareDelegate<T> Compare)
	{
		if (Array == nullptr || Size < 2)
		{
			return;
		}

		for (uint32 Index = 1; Index < Size; Index++)
		{
			T Temp = Array[Index];
			Suint32 Index2 = Index - 1;

			while (Index2 >= 0 && Compare(Temp, Array[Index2]))
			{
				Array[Index2 + 1] = Array[Index2];
				Index2--;
			}
			Array[Index2 + 1] = Temp;
		}
	}	

	template<typename T>
	FORCEINLINE static void CombSort(T Array[], const uint32 Size, TCompareDelegate<T> Compare)
	{
		const float ShrinkFactor = 1.247330950103979f;

		if (Array == nullptr || Size < 2)
		{
			return;
		}

		uint32 Gap = static_cast<uint32>(Size / ShrinkFactor);
		uint32 Index = 0;

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
			Gap = static_cast<uint32>(Gap / ShrinkFactor);
		}
	}

	template<typename T>
	FORCEINLINE static void ShellSort(T Array[], const uint32 Size, TCompareDelegate<T> Compare)
	{
		if (Array == nullptr || Size < 2)
		{
			return;
		}

		bool bHasBeenSwapped = true;
		uint32 Gap = Size;

		while (bHasBeenSwapped && Gap > 1)
		{
			bHasBeenSwapped = false;

			Gap = (Gap + 1) / 2;

			for (uint32 Index = 0; Index < Size - Gap; Index++)
			{
				if (Compare(Array[Index + Gap], Array[Index]))
				{
					Swap(&Array[Index + Gap], &Array[Index]);
					bHasBeenSwapped = true;
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

#pragma warning(pop)