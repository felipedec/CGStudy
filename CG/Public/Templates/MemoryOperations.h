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

#include "HAL/Platform.h"
#include "Templates/IsTriviallyCopyAssignable.h"
#include "Templates/IsBitwiseConstructible.h"
#include "Templates/IsTriviallyDestructible.h"

class FMemory
{
public:


	FORCEINLINE static void* Memset(void* Dest, uint8 Char, SIZE_T Count)
	{

	}


	FORCEINLINE static void* Memmove(void* Dest, const void* Src, SIZE_T Count)
	{

	}

	FORCEINLINE static int32 Memcmp(const void* Buf1, const void* Buf2, SIZE_T Count)
	{

	}

};

/*----------------------------------------------------------------------------	
			Private.
----------------------------------------------------------------------------*/

namespace Engine_Private
{
	template <typename DestinationElementType, typename SourceElementType>
	struct TCanBitwiseRelocate : TOr
	<
		TIsSame<DestinationElementType, SourceElementType>,
		TAnd
		<
			TIsBitwiseConstructible<DestinationElementType, SourceElementType>,
			TIsTriviallyDestructible<SourceElementType>
		>
	> {};


	template<typename T> struct TIsBytewiseComparable : TOr<TIsEnum<T>, TIsArithmetic<T>, TIsPointer<T>> {};
}

/*----------------------------------------------------------------------------	
			DefaultConstructItems.
----------------------------------------------------------------------------*/

template <typename ElementType>
FORCEINLINE typename TEnableIf<!TIsZeroConstructType<ElementType>::Value, void>::Type DefaultConstructItems(void* Address, int32 Count)
{
	ElementType* Element = (ElementType*)Address;

	while (Count)
	{
		new (Element) ElementType;

		++Element;
		--Count;
	}
}


template <typename ElementType>
FORCEINLINE typename TEnableIf<TIsZeroConstructType<ElementType>::Value, void>::Type DefaultConstructItems(void* Elements, int32 Count)
{
	FMemory::Memset(Elements, 0, sizeof(ElementType) * Count);
}

/*----------------------------------------------------------------------------	
			DestructItem.
----------------------------------------------------------------------------*/

template <typename ElementType>
FORCEINLINE typename TEnableIf<!TIsTriviallyDestructible<ElementType>::Value, void>::Type DestructItem(ElementType* Element)
{
	typedef ElementType DestructItemsElementTypeTypedef;
	Element->DestructItemsElementTypeTypedef::~DestructItemsElementTypeTypedef();
}


template <typename ElementType>
FORCEINLINE typename TEnableIf<TIsTriviallyDestructible<ElementType>::Value, void>::Type DestructItem(ElementType* Element)
{
}

/*----------------------------------------------------------------------------	
			DestructItems.
----------------------------------------------------------------------------*/

template <typename ElementType>
FORCEINLINE typename TEnableIf<!TIsTriviallyDestructible<ElementType>::Value, void>::Type DestructItems(ElementType* Element, int32 Count)
{
	while (Count)
	{
		typedef ElementType DestructItemsElementTypeTypedef;
		Element->DestructItemsElementTypeTypedef::~DestructItemsElementTypeTypedef();

		++Element;
		--Count;
	}
}


template <typename ElementType>
FORCEINLINE typename TEnableIf<TIsTriviallyDestructible<ElementType>::Value, void>::Type DestructItems(ElementType* Elements, int32 Count)
{
}

/*----------------------------------------------------------------------------	
			ConstructItems.
----------------------------------------------------------------------------*/

template <typename DestinationElementType, typename SourceElementType>
FORCEINLINE typename TEnableIf<!TIsBitwiseConstructible<DestinationElementType, SourceElementType>::Value, void>::Type ConstructItems(void* Dest, const SourceElementType* Source, int32 Count)
{
	while (Count)
	{
		new (Dest) DestinationElementType(*Source);

		++(DestinationElementType*&)Dest;
		++Source;
		--Count;
	}
}


template <typename DestinationElementType, typename SourceElementType>
FORCEINLINE typename TEnableIf<TIsBitwiseConstructible<DestinationElementType, SourceElementType>::Value, void>::Type ConstructItems(void* Dest, const SourceElementType* Source, int32 Count)
{
	//FMemory::Memcpy(Dest, Source, sizeof(SourceElementType) * Count);
}

/*----------------------------------------------------------------------------	
			DestructItems.
----------------------------------------------------------------------------*/

template <typename ElementType>
FORCEINLINE typename TEnableIf<!TIsTriviallyCopyAssignable<ElementType>::Value, void>::Type CopyAssignItems(ElementType* Dest, const ElementType* Source, int32 Count)
{
	while (Count)
	{
		*Dest = *Source;

		++Dest;
		++Source;
		--Count;
	}
}


template <typename ElementType>
FORCEINLINE typename TEnableIf<TIsTriviallyCopyAssignable<ElementType>::Value, void>::Type CopyAssignItems(ElementType* Dest, const ElementType* Source, int32 Count)
{
	//FMemory::Memcpy(Dest, Source, sizeof(ElementType) * Count);
}

/*----------------------------------------------------------------------------	
			RelocateConstructItems.
----------------------------------------------------------------------------*/

template <typename DestinationElementType, typename SourceElementType>
FORCEINLINE typename TEnableIf<!Engine_Private::TCanBitwiseRelocate<DestinationElementType, SourceElementType>::Value, void>::Type RelocateConstructItems(void* Dest, const SourceElementType* Source, int32 Count)
{
	while (Count)
	{
		typedef SourceElementType RelocateConstructItemsElementTypeTypedef;

		new (Dest) DestinationElementType(*Source);
		++(DestinationElementType*&)Dest;
		(Source++)->RelocateConstructItemsElementTypeTypedef::~RelocateConstructItemsElementTypeTypedef();
		--Count;
	}
}

template <typename DestinationElementType, typename SourceElementType>
FORCEINLINE typename TEnableIf<Engine_Private::TCanBitwiseRelocate<DestinationElementType, SourceElementType>::Value, void>::Type RelocateConstructItems(void* Dest, const SourceElementType* Source, int32 Count)
{
	FMemory::Memmove(Dest, Source, sizeof(SourceElementType) * Count);
}

/*----------------------------------------------------------------------------	
			MoveConstructItems.
----------------------------------------------------------------------------*/

template <typename ElementType>
FORCEINLINE typename TEnableIf<!TIsTriviallyCopyConstructible<ElementType>::Value, void>::Type MoveConstructItems(void* Dest, const ElementType* Source, int32 Count)
{
	while (Count)
	{
		new (Dest) ElementType((ElementType&&)*Source);

		++(ElementType*&)Dest;
		++Source;
		--Count;
	}
}

template <typename ElementType>
FORCEINLINE typename TEnableIf<TIsTriviallyCopyConstructible<ElementType>::Value, void>::Type MoveConstructItems(void* Dest, const ElementType* Source, int32 Count)
{
	FMemory::Memmove(Dest, Source, sizeof(ElementType) * Count);
}

 /*----------------------------------------------------------------------------	
			MoveAssignItems.
----------------------------------------------------------------------------*/

template <typename ElementType>
FORCEINLINE typename TEnableIf<!TIsTriviallyCopyAssignable<ElementType>::Value, void>::Type MoveAssignItems(ElementType* Dest, const ElementType* Source, int32 Count)
{
	while (Count)
	{
		*Dest = (ElementType&&)*Source;

		++Dest;
		++Source;
		--Count;
	}
}

template <typename ElementType>
FORCEINLINE typename TEnableIf<TIsTriviallyCopyAssignable<ElementType>::Value, void>::Type MoveAssignItems(ElementType* Dest, const ElementType* Source, int32 Count)
{
	FMemory::Memmove(Dest, Source, sizeof(ElementType) * Count);
}

 /*----------------------------------------------------------------------------	
			CompareItems.
----------------------------------------------------------------------------*/

template <typename ElementType>
FORCEINLINE typename TEnableIf<Engine_Private::TIsBytewiseComparable<ElementType>::Value, bool>::Type CompareItems(const ElementType* A, const ElementType* B, int32 Count)
{
	return !FMemory::Memcmp(A, B, sizeof(ElementType) * Count);
}


template <typename ElementType>
FORCEINLINE typename TEnableIf<!Engine_Private::TIsBytewiseComparable<ElementType>::Value, bool>::Type CompareItems(const ElementType* A, const ElementType* B, int32 Count)
{
	while (Count)
	{
		if (!(*A == *B))
		{
			return false;
		}

		++A;
		++B;
		--Count;
	}

	return true;
}