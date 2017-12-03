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

#pragma once


#include "Core.h"


template <typename TElement, uint32 NumElements, uint32 Alignment = alignof(TElement)>
class TStaticArray
{
private:

	TAlignedBytes<sizeof(TElement), Alignment> Elements[NumElements];

public:

	TStaticArray()
	{
		for (uint32 ElementIndex = 0; ElementIndex < NumElements; ++ElementIndex)
		{
			new(&(*this)[ElementIndex]) TElement;
		}
	}

	TStaticArray(TStaticArray&& Other)
	{
		MoveConstructItems((void*)Elements, (const TElement*)Other.Elements, NumElements);
	}

	TStaticArray(const TStaticArray& Other)
	{
		ConstructItems<TElement>((void*)Elements, (const TElement*)Other.Elements, NumElements);
	}

	TStaticArray& operator=(const TStaticArray& Other)
	{
		CopyAssignItems((TElement*)Elements, (const TElement*)Other.Elements, NumElements);
		return *this;
	}

	~TStaticArray()
	{
		DestructItems((TElement*)Elements, NumElements);
	}

public:

	friend bool operator==(const TStaticArray& A, const TStaticArray& B)
	{
		for (uint32 ElementIndex = 0; ElementIndex < NumElements; ++ElementIndex)
		{
			if (!(A[ElementIndex] == B[ElementIndex]))
			{
				return false;
			}
		}
		return true;
	}

	friend bool operator!=(const TStaticArray& A, const TStaticArray& B)
	{
		for (uint32 ElementIndex = 0; ElementIndex < NumElements; ++ElementIndex)
		{
			if (!(A[ElementIndex] == B[ElementIndex]))
			{
				return true;
			}
		}
		return false;
	}

public:

	FORCEINLINE TElement& operator[](uint32 Index)
	{
		check(Index < NumElements);
		return *(TElement*)&Elements[Index];
	}

	FORCEINLINE const TElement& operator[](uint32 Index) const
	{
		check(Index < NumElements);
		return *(const TElement*)&Elements[Index];
	}

public:

	FORCEINLINE int32 Num() const
	{
		return NumElements;
	}
};
