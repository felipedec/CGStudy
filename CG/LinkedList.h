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

#pragma once

#include "CoreFwd.h"

// Declaration Forward
template<typename T>
struct TLinkedList;

template<typename T>
struct TBidirectionalNode
{
public:
  
	friend TLinkedList<T>;

public:

	TBidirectionalNode<T>& GetNext()
	{
		return *Next;
	}

	TBidirectionalNode<T>& GetPrevious()
	{
		return *GetPrevious();
	}

private:

	/** Próximo nodo */
	TBidirectionalNode<T>* Next;

	/** Obtém o nó anterior no LinkedList<T> */
	TBidirectionalNode<T>* Previous;

	/** Obtém o valor contido no nó */
	T Value;

	/** Obtém o TLinkedList<T> ao qual o TBidirectionalNode<T> pertence */
	const TLinkedList<T>* List;

public:

	FORCEINLINE TBidirectionalNode(const T& InValue, const TLinkedList<T>* InList) : List(InList)
	{
		Value = InValue;
	}

	FORCEINLINE TBidirectionalNode(const TBidirectionalNode<T>& Other) : List(Other.List)
	{
		Value = Other.Value;
		Next = Other.Next;
		Previous = Other.Previous;
	}
	
	FORCEINLINE ~TBidirectionalNode()
	{
		Next = nullptr;
		Previous = nullptr;
	}

public:

	FORCEINLINE operator T&()
	{
		return Value;
	}
};

template<typename T> 
struct TLinkedList
{
private:

	/** Primeiro nodo */
	TBidirectionalNode<T>* First;

	/** Ultímo nodo */
	TBidirectionalNode<T>* Last;

	/** Número de nós que realmente estão contidos na TBidirectionalNode<T> */
	uint32_t Count;

public:

	FORCEINLINE ~TLinkedList()
	{
		Clear();
	}

public:

	FORCEINLINE TBidirectionalNode<T>* AddAfter(TBidirectionalNode<T>* NodePtr, const T& Value)
	{
		CHECKF(NodePtr == nullptr, ELogSeverity::Warning, "NodePtr has to be different than null.");
		CHECKF(Contains(*NodePtr), ELogSeverity::Warning, "Passed node doesn't contains this list.");

		TBidirectionalNode<T>* NewNode = new TBidirectionalNode<T>(Value, this);
		Count++;

		NewNode->Previous = NodePtr;
		NewNode->Next = NodePtr->Next;

		NodePtr->Next = NewNode;

		if (NodePtr == Last)
		{
			Last = NewNode;
		}

		return NewNode;
	}

	FORCEINLINE static TBidirectionalNode<T>* AddBefore(TBidirectionalNode<T>* NodePtr, const T& Value)
	{
		CHECKF(NodePtr == nullptr, ELogSeverity::Warning, "NodePtr has to be different than null.");
		CHECKF(Contains(*NodePtr), ELogSeverity::Warning, "Passed node doesn't contains this list.");

		TBidirectionalNode<T>* NewNode = new TBidirectionalNode<T>(Value, this);
		Count++;

		NewNode->Previous = NodePtr->Previous;
		NewNode->Next = NodePtr;

		NodePtr->Previous = NewNode;

		if (NodePtr == First)
		{
			First = NewNode;
		}
		
		return NewNode;
	}

	FORCEINLINE TBidirectionalNode<T>* AddFirst(const T& Value)
	{
		if (First == nullptr)
		{
			First = new TBidirectionalNode<T>(Value, this);
			Last = First;

			Count++;
			
			return First;
		}

		return AddBefore(First);
	}

	FORCEINLINE TBidirectionalNode<T>* AddLast(const T& Value)
	{
		if (Last == nullptr)
		{
			Last = new TBidirectionalNode<T>(Value, this);
			First = Last;

			Count++;

			return Last;
		}

		return AddAfter(Last);
	}

	FORCEINLINE void Clear()
	{
		while (!IsEmpty())
		{
			RemoveFirst();
		}
	}

	FORCEINLINE void RemoveFirst()
	{
		if (First == nullptr)
		{
			return;
		}

		if (First == Last)
		{
			delete First;

			First = nullptr;
			Last = nullptr;
		}

		TBidirectionalNode<T>* Garbage = First;
		
		First = First->Next;

		Count--;
		delete Garbage;
	}

	FORCEINLINE void RemoveLast()
	{
		if (Last == nullptr)
		{
			return;
		}

		if (First == Last)
		{
			delete First;

			First = nullptr;
			Last = nullptr;
		}

		TBidirectionalNode<T>* Garbage = Last;

		Last = Last->Previous;

		Count--;
		delete Garbage;
	}

	FORCEINLINE TBidirectionalNode<T>* Find(const T& Value) const
	{
		for (TBidirectionalNode<T>* Aux = First; Aux; Aux = Aux->Next)
		{
			if (Aux->Value == Value)
			{
				return Aux;
			}
		}
		return nullptr;
	}

	FORCEINLINE TBidirectionalNode<T>* FindLast(const T& Value) const
	{
		for (TBidirectionalNode<T>* Aux = Last; Aux; Aux = Aux->Previous)
		{
			if (Aux->Value == Value)
			{
				return Aux;
			}
		}
		return nullptr;
	}


public:
	
	FORCEINLINE bool Contains(const T& Value) const
	{
		for (TBidirectionalNode<T>* Aux = First; Aux; Aux = Aux->Next)
		{
			if (Aux->Value == Value)
			{
				return true;
			}
		}
		return false;
	}

	FORCEINLINE bool Contains(const TBidirectionalNode<T>& Node) const
	{
		return Node != nullptr && Node.List == this;
	}

	FORCEINLINE bool IsEmpty() const
	{
		return First == Last;
	}

	FORCEINLINE uint32_t GetCount() const
	{
		return Count;
	}
};