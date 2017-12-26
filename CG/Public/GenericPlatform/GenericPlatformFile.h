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

#include "CoreTypes.h" 

union FRect
{
public:
   
   struct 
   {
      FVector2 Position;
      FVector2 Size;
   };

   struct
   {
      float X, Y, Width, Height;
   };

   float Components[4];

public:

   FORCEINLINE FRect() = default;

   FORCEINLINE FRect(const FVector2& InSize, const FVector2& InPosition) :
      FRect(InPosition.X, InPosition.Y, InSize.X, InSize.Y)
   { }

   FORCEINLINE FRect(const FVector2& Min, const FVector2& Max) :
      FRect(Min.X, Min.Y, Max.X - Min.X, Max.Y - Min.Y)
   { }

   FORCEINLINE FRect(const float X, const float Y, const float Width, const float Height) :
      Position(X, Y),
      Size(Width, Height)
   { }

public:

   FORCEINLINE void SetCenter(const FVector2 Center)
   {
      Position = Center - Size / 2;
   }

public:

   FORCEINLINE bool Contains(const FVector2& P) const
   {
      return P.X >= X && P.Y >= Y && P.X <= (X + Width)  && P.Y <= (Y + Height);
   }
};

class FScreen;

class FGenericPlatformScreen
{
protected:

   FRect Position;

public:

   FORCEINLINE FGenericPlatformScreen(const FRect& InPosition) :
      Position(InPosition)
   { }

public:

   virtual FORCEINLINE void Resize(const FVector2& NewSize) = 0;

public:

   FORCEINLINE const FRect& GetRect() const
   {
      return Position;
   }

};

typedef FGenericPlatformScreen FPlatformScreen;

template <typename T>
struct TDefaultDelete
{
   TDefaultDelete() = default;
   TDefaultDelete(const TDefaultDelete&) = default;
   ~TDefaultDelete() = default;

   template <typename U, typename = typename TEnableIf<TPointerIsConvertibleFromTo<U, T>::Value>::Type>
   TDefaultDelete(const TDefaultDelete<U>&)
   { }

public:

   TDefaultDelete& operator=(const TDefaultDelete&) = default;

   template <typename U, typename = typename TEnableIf<TPointerIsConvertibleFromTo<U, T>::Value>::Type>
   TDefaultDelete& operator=(const TDefaultDelete<U>&)
   {
      return *this;
   }

   void operator()(T* Ptr) const
   {
      delete Ptr;
   }
};

template <typename T>
struct TDefaultDelete<T[]>
{
   TDefaultDelete() = default;
   TDefaultDelete(const TDefaultDelete&) = default;
   ~TDefaultDelete() = default;

   template <typename U, typename = typename TEnableIf<TPointerIsConvertibleFromTo<U[], T[]>::Value>::Type>
   TDefaultDelete(const TDefaultDelete<U[]>&)
   { }

public:

   TDefaultDelete& operator=(const TDefaultDelete&) = default;

   template <typename U, typename = typename TEnableIf<TPointerIsConvertibleFromTo<U[], T[]>::Value>::Type>
   TDefaultDelete& operator=(const TDefaultDelete<U[]>&)
   {
      return *this;
   }

   template <typename U>
   typename TEnableIf<TPointerIsConvertibleFromTo<U[], T[]>::Value>::Type operator()(U* Ptr) const
   {
      delete[] Ptr;
   }
};