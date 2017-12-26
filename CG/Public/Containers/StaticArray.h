// Código baseado no código aberto da Unreal Engine

#pragma once

#include "Core.h"

template <typename ElementType, uint32 NumElements, uint32 Alignment = alignof(ElementType)>
class TStaticArray
{
private:

   TAlignedBytes<sizeof(ElementType), Alignment> Elements[NumElements]; 

public:

   FORCEINLINE TStaticArray()
   {
      for (uint32 ElementIndex = 0; ElementIndex < NumElements; ++ElementIndex)
      {
         new(&(*this)[ElementIndex]) ElementType;
      }
   }

   FORCEINLINE TStaticArray(TStaticArray&& Other)
   {
      MoveConstructItems((void*)Elements, (const ElementType*)Other.Elements, NumElements);
   }

   FORCEINLINE TStaticArray(const TStaticArray& Other)
   {
      ConstructItems<ElementType>((void*)Elements, (const ElementType*)Other.Elements, NumElements);
   }

   FORCEINLINE TStaticArray& operator=(const TStaticArray& Other)
   {
      CopyAssignItems((ElementType*)Elements, (const ElementType*)Other.Elements, NumElements);
      return *this;
   }

   FORCEINLINE ~TStaticArray()
   {
      DestructItems((ElementType*)Elements, NumElements);
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

   FORCEINLINE ElementType& operator[](uint32 Index)
   {
      check(Index < NumElements);
      return *(ElementType*)&Elements[Index];
   }

   FORCEINLINE const ElementType& operator[](uint32 Index) const
   {
      check(Index < NumElements);
      return *(const ElementType*)&Elements[Index];
   }

public:

   CONSTEXPR int32 Num() const
   {
      return NumElements;
   }
};
