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

#include "Macros.h"
#include "HAL/Platform.h"

/*----------------------------------------------------------------------------
			Utilitário(s) para evitar um pouco de repetição de código.
----------------------------------------------------------------------------*/

namespace Engine_Private
{
	template<typename T>
	struct TType
	{
		using Type = T;
	};
}

#define IMPLEMENT_USING_TYPE(Trait) template<typename T> using Trait ## Type = typename Trait<T>::Type;
#define IMPLEMENT_VALUE_METHOD(Trait) template<typename T> CONSTEXPR bool Trait = T ## Trait<T>::Value; 

/*----------------------------------------------------------------------------
			Macros para os type traits intrínsecos do compilador.
----------------------------------------------------------------------------*/

#define IS_ENUM(T) __is_enum(T)
#define IS_UNION(T) __is_union(T)
#define IS_ABSTRACT(T) __is_abstract(T)
#define IS_POD(T) __is_pod(T)
#define HAS_TRIVIAL_DESTRUCTOR(T) __has_trivial_destructor(T)
#define HAS_TRIVIAL_ASSIGN(T) __has_trivial_assign(T)
#define HAS_TRIVIAL_COPY(T) __has_trivial_copy(T)


/*----------------------------------------------------------------------------
			TIntegralConst.
----------------------------------------------------------------------------*/

template<typename T, T U>
struct TIntegralConst
{
	CONSTEXPR static T Value = U;
};

/*----------------------------------------------------------------------------
			TConditional.
----------------------------------------------------------------------------*/

template<bool, typename TrueType, typename FalseType> struct TConditional : Engine_Private::TType<FalseType> { };
template<typename TrueType, typename FalseType> struct TConditional<true, TrueType, FalseType> : Engine_Private::TType<TrueType> { };

template<bool Predicate, typename TrueType, typename FalseType>
using ConditionalType = typename TConditional<Predicate, TrueType, FalseType>::Type;

/*----------------------------------------------------------------------------
			TSelectPlatformType.
----------------------------------------------------------------------------*/

template<typename T32Bits, typename T64Bits> struct TSelectPlatformType : TConditional<sizeof(void*) == 4, T32Bits, T64Bits> { };

/*----------------------------------------------------------------------------
			TConstBoolean, FTrueType, TFalseType.
----------------------------------------------------------------------------*/

template<bool Predicate> struct TConstBoolean : TIntegralConst<bool, Predicate> { };

struct FTrueType : TConstBoolean<true> { };
struct TFalseType : TConstBoolean<false> { };

/*----------------------------------------------------------------------------
			TAnd.
----------------------------------------------------------------------------*/

template <typename... Types> struct TAnd;
template <bool Lhs, typename... Rhs> struct TAndValue : TConstBoolean<TAnd<Rhs...>::Value> {};
template <typename... Rhs> struct TAndValue<false, Rhs...> : TConstBoolean<false> {};
template <typename Lhs, typename... Rhs> struct TAnd<Lhs, Rhs...> : TAndValue<Lhs::Value, Rhs...> {};
template <> struct TAnd<> : TConstBoolean<true> {};

/*----------------------------------------------------------------------------
			TOr.
----------------------------------------------------------------------------*/

template <typename... Types> struct TOr;
template <bool Lhs, typename... Rhs> struct TOrValue : TConstBoolean<TOr<Rhs...>::Value> {};
template <typename... Rhs> struct TOrValue<true, Rhs...> : TConstBoolean<true> {};
template <typename Lhs, typename... Rhs> struct TOr<Lhs, Rhs...> : TOrValue<Lhs::Value, Rhs...> {};
template <> struct TOr<> : TConstBoolean<false> {};

/*----------------------------------------------------------------------------
			TNot.
----------------------------------------------------------------------------*/

template <typename Type> struct TNot : TConstBoolean<!Type::Value> {};

/*----------------------------------------------------------------------------
			TEnableIf.
----------------------------------------------------------------------------*/

template<bool Predicate, typename T = void> struct TEnableIf { };
template<typename T> struct TEnableIf<true, T> : Engine_Private::TType<T> { };

/*----------------------------------------------------------------------------
			TRemoveConst.
----------------------------------------------------------------------------*/

template<typename T> struct TRemoveConst : Engine_Private::TType<T> { };
template<typename T> struct TRemoveConst<const T> : TRemoveConst<T> { };

IMPLEMENT_USING_TYPE(TRemoveConst)

/*----------------------------------------------------------------------------
			TRemoveVolatile.
----------------------------------------------------------------------------*/

template<typename T> struct TRemoveVolatile : Engine_Private::TType<T> { };
template<typename T> struct TRemoveVolatile<volatile T> : TRemoveVolatile<T> { };

IMPLEMENT_USING_TYPE(TRemoveVolatile)

/*----------------------------------------------------------------------------
			TRemoveConstAndVolatite.
----------------------------------------------------------------------------*/

template<typename T> struct TRemoveCV : Engine_Private::TType<TRemoveConstType<TRemoveVolatileType<T>>> { };

IMPLEMENT_USING_TYPE(TRemoveCV)

/*----------------------------------------------------------------------------
			TRemovePointer.
----------------------------------------------------------------------------*/

template<typename T> struct TRemovePointer : Engine_Private::TType<T> { };
template<typename T> struct TRemovePointer<T*> : TRemovePointer<T> { };

IMPLEMENT_USING_TYPE(TRemovePointer)

/*----------------------------------------------------------------------------
			TRemoveReference.
----------------------------------------------------------------------------*/

template<typename T> struct TRemoveReference : Engine_Private::TType<T> { };
template<typename T> struct TRemoveReference<T&> : TRemoveReference<T> {};

IMPLEMENT_USING_TYPE(TRemoveReference)

/*----------------------------------------------------------------------------
			TRemovePointerAndReference.
----------------------------------------------------------------------------*/

template<typename T> 
struct TRemovePointerAndReference : Engine_Private::TType<TRemovePointerType<TRemoveReferenceType<T>>> { };

IMPLEMENT_USING_TYPE(TRemovePointerAndReference)

/*----------------------------------------------------------------------------
			TRemoveExtend.
----------------------------------------------------------------------------*/

template<typename T> struct TRemoveExtend : Engine_Private::TType<T> { };
template<typename T> struct TRemoveExtend<T[]> : TRemoveExtend<T> { };
template<typename T, uint32 Size> struct TRemoveExtend<T[Size]> : TRemoveExtend<T> { };

IMPLEMENT_USING_TYPE(TRemoveExtend)

/*----------------------------------------------------------------------------
			TRemovePointerReferenceAndArray.
----------------------------------------------------------------------------*/

template<typename T> 
struct TRemovePointerReferenceAndExtend : Engine_Private::TType<TRemovePointerAndReferenceType<TRemoveExtendType<T>>> { };

IMPLEMENT_USING_TYPE(TRemovePointerReferenceAndExtend)

/*----------------------------------------------------------------------------
			TIsSame.
----------------------------------------------------------------------------*/

template<typename T, typename U> struct TIsSame : TFalseType { };
template<typename T> struct TIsSame<T, T> : FTrueType { };

template<typename T, typename U>
CONSTEXPR bool IsSame = TIsSame<T, U>::Value;

/*----------------------------------------------------------------------------
         TPointerIsConvertibleFromTo.
----------------------------------------------------------------------------*/

template <typename From, typename To>
struct TPointerIsConvertibleFromTo
{
private:
   static uint8 Test(...);
   static uint16 Test(To*);

public:
   CONSTEXPR static bool Value = sizeof(Test((From*)nullptr)) == sizeof(uint8) ? false : true;
};

/*----------------------------------------------------------------------------
			TIsIntegral.
----------------------------------------------------------------------------*/

namespace Engine_Private
{
	template<typename T> struct TIsIntegralHelper : TFalseType { };

	template<> struct TIsIntegralHelper<bool> : FTrueType { };
	template<> struct TIsIntegralHelper<char> : FTrueType { };
	template<> struct TIsIntegralHelper<char16_t> : FTrueType { };
	template<> struct TIsIntegralHelper<char32_t> : FTrueType { };
	template<> struct TIsIntegralHelper<wchar_t> : FTrueType { };
	template<> struct TIsIntegralHelper<short> : FTrueType { };
	template<> struct TIsIntegralHelper<int> : FTrueType { };
	template<> struct TIsIntegralHelper<long> : FTrueType { };
	template<> struct TIsIntegralHelper<long long> : FTrueType { };
}

template<typename T> struct TIsIntegral : Engine_Private::TIsIntegralHelper<TRemoveCVType<T>> { };

IMPLEMENT_VALUE_METHOD(IsIntegral)

/*----------------------------------------------------------------------------
			TIsFloatingPoint.
----------------------------------------------------------------------------*/

namespace Engine_Private
{
	template<typename T> struct TIsFloatingPointHelper : TFalseType { };

	template<> struct TIsFloatingPointHelper<float> : FTrueType { };
	template<> struct TIsFloatingPointHelper<double> : FTrueType { };
	template<> struct TIsFloatingPointHelper<long double> : FTrueType { };
}

template<typename T> struct TIsFloatingPoint : Engine_Private::TIsFloatingPointHelper<TRemoveCVType<T>> { };

IMPLEMENT_VALUE_METHOD(IsFloatingPoint)

/*----------------------------------------------------------------------------
			TIsFunction.
----------------------------------------------------------------------------*/

template<typename T> struct TIsFunction : TFalseType { };

template<typename Return, typename... Params> struct TIsFunction<Return(Params...)> : FTrueType { };
template<typename Return, typename... Params> struct TIsFunction<Return(Params...) const> : FTrueType { };

IMPLEMENT_VALUE_METHOD(IsFunction)

/*----------------------------------------------------------------------------
			TIsMemberFunctionPointer.
----------------------------------------------------------------------------*/

namespace Engine_Private
{
	template<typename T> struct TIsMemberFunctionPointerHelper : TFalseType { };
	template<typename T, typename U> struct TIsMemberFunctionPointerHelper<T U::*> : TIsFunction<T> { };
}

template<typename T> struct TIsMemberFunctionPointer : Engine_Private::TIsMemberFunctionPointerHelper<TRemoveCVType<T>> { };

IMPLEMENT_VALUE_METHOD(IsMemberFunctionPointer)

/*----------------------------------------------------------------------------
			HasSignature Traits.
----------------------------------------------------------------------------*/

#define DECLARE_HAS_MEMBER_FUNCTION(TraitName, FunctionName, Signature) \
WARNING(push) \
WARNING(disable:4067) \
template <typename U> \
struct TraitName \
{ \
private: \
   template<typename T, T> struct Helper; \
   template<typename T> static uint8 Check(Helper<Signature, &T::FunctionName>*); \
   template<typename T> static uint32 Check(...); \
public: \
   CONSTEXPR static bool Value = sizeof(Check<U>(0)) == sizeof(uint8); \
}; \
WARNING(pop) \

#define DECLARE_HAS_STATIC_FUNCTION(TraitName, FunctionName, Signature) \
WARNING(push) \
WARNING(disable:4067) \
template <typename U> \
struct TraitName \
{ \
private: \
   template<typename T, T> struct Helper; \
   template<typename T> static uint8 Check(Helper<Signature, T::FunctionName>*); \
   template<typename T> static uint32 Check(...); \
public: \
   CONSTEXPR static bool Value = sizeof(Check<U>(0)) == sizeof(uint8); \
}; \
WARNING(pop) \

/*----------------------------------------------------------------------------
			TIsArray.
----------------------------------------------------------------------------*/

template<typename T> struct TIsArray : TFalseType { };
template<typename T> struct TIsArray<T[]> : FTrueType { };
template<typename T, uint32 Size> struct TIsArray<T[Size]> : FTrueType { };

IMPLEMENT_VALUE_METHOD(IsArray)

/*----------------------------------------------------------------------------
			TIsVoid.
----------------------------------------------------------------------------*/

namespace Engine_Private
{
	template<typename T> struct TIsVoidHelper : TFalseType { };
	template<> struct TIsVoidHelper<void> : FTrueType { };
}

template<typename T> struct TIsVoid :	Engine_Private::TIsVoidHelper<TRemoveCVType<T>> { };

IMPLEMENT_VALUE_METHOD(IsVoid)

/*----------------------------------------------------------------------------
			TIsNullPointer.
----------------------------------------------------------------------------*/

namespace Engine_Private
{
	template<typename T> struct TIsNullPointerHelper : TFalseType { };
	template<> struct TIsNullPointerHelper<TYPE_OF_NULLPTR> : FTrueType { };
}

template<typename T> struct TIsNullPointer : Engine_Private::TIsNullPointerHelper<TRemoveCVType<T>> { };

IMPLEMENT_VALUE_METHOD(IsNullPointer)

/*----------------------------------------------------------------------------
			TIsPointer.
----------------------------------------------------------------------------*/

template<typename T> struct TIsPointer : TFalseType { };
template<typename T> struct TIsPointer<T*> : FTrueType { };

IMPLEMENT_VALUE_METHOD(IsPointer)

/*----------------------------------------------------------------------------
			TIsMemberPointer.
----------------------------------------------------------------------------*/

namespace Engine_Private
{
	template<typename T> struct TIsMemberPointerHelper : TFalseType { };
	template<typename T, typename U> struct TIsMemberPointerHelper<T U::*> : FTrueType { };
}

template<typename T> struct TIsMemberPointer : Engine_Private::TIsMemberPointerHelper<TRemoveCVType<T>> { };

IMPLEMENT_VALUE_METHOD(IsMemeberPointer)

/*----------------------------------------------------------------------------
			TIsReference.
----------------------------------------------------------------------------*/

template<typename T> struct TIsReference : TFalseType { };
template<typename T> struct TIsReference<T&> : FTrueType { };

IMPLEMENT_VALUE_METHOD(IsReference)

/*----------------------------------------------------------------------------
			TIsConst.
----------------------------------------------------------------------------*/

namespace Engine_Private
{
	template<typename T> struct TIsConstHelper : TFalseType { };
	template<typename T> struct TIsConstHelper<const T> : FTrueType { };
}

template<typename T> struct TIsConst : Engine_Private::TIsConstHelper<TRemovePointerReferenceAndExtendType<T>> { };

IMPLEMENT_VALUE_METHOD(IsConst)

/*----------------------------------------------------------------------------
			TIsVolatile.
----------------------------------------------------------------------------*/

namespace Engine_Private
{
	template<typename T> struct TIsVolatileHelper : TFalseType { };
	template<typename T> struct TIsVolatileHelper<volatile T> : FTrueType { };
}

template<typename T> struct TIsVolatile : Engine_Private::TIsVolatileHelper<TRemovePointerReferenceAndExtend<T>> { };

IMPLEMENT_VALUE_METHOD(IsVolatile)

/*----------------------------------------------------------------------------
			TIsUnion.
----------------------------------------------------------------------------*/

template<typename T> struct TIsUnion : TConstBoolean<IS_UNION(T)> { };

IMPLEMENT_VALUE_METHOD(IsUnion)

/*----------------------------------------------------------------------------
			TIsEnum.
----------------------------------------------------------------------------*/

template<typename T> struct TIsEnum : TConstBoolean<IS_ENUM(T)> { };

IMPLEMENT_VALUE_METHOD(IsEnum)

/*----------------------------------------------------------------------------
			TIsAbstract.
----------------------------------------------------------------------------*/

template <typename T> struct TIsAbstract : TConstBoolean<IS_ABSTRACT(T)> {};

IMPLEMENT_VALUE_METHOD(IsAbstract)

/*----------------------------------------------------------------------------
			TIsStruct.
----------------------------------------------------------------------------*/

template<typename T>
struct TIsStruct
{
private:

	template<typename U> static uint32 Test(int32 U::*);
	template<typename U> static uint8 Test(...);

public:

	CONSTEXPR static bool Value = sizeof(Test<T>(0)) == sizeof(uint32) && !IsUnion<T>();
};

IMPLEMENT_VALUE_METHOD(IsStruct)

/*----------------------------------------------------------------------------
			TIsArithmetic.
----------------------------------------------------------------------------*/

template<typename T> struct TIsArithmetic : TOr<TIsIntegral<T>, TIsFloatingPoint<T>> { };

IMPLEMENT_VALUE_METHOD(IsArithmetic)

/*----------------------------------------------------------------------------
			TIsUnsigned.
----------------------------------------------------------------------------*/

namespace Engine_Private
{
	template<bool, typename T> struct TIsUnsignedHelper : TFalseType { };

	template<typename T> struct TIsUnsignedHelper<true, T> : TConstBoolean<T(0) < T(-1)> { };
}

template<typename T> struct TIsUnsigned : Engine_Private::TIsUnsignedHelper<IsArithmetic<T>, T> { };

IMPLEMENT_VALUE_METHOD(IsUnsigned)

/*----------------------------------------------------------------------------
			TIsSigned.
----------------------------------------------------------------------------*/

template<typename T> struct TIsSigned : TNot<TIsUnsigned<T>> { };

IMPLEMENT_VALUE_METHOD(IsSigned)

/*----------------------------------------------------------------------------
			IsFundamental.
----------------------------------------------------------------------------*/

template<typename T> struct TIsFundamental : TOr<TIsArithmetic<T>, TIsVoid<T>, TIsSame<TYPE_OF_NULLPTR, T>> { };

IMPLEMENT_VALUE_METHOD(IsFundamental)

/*----------------------------------------------------------------------------
         TIsPODType.
----------------------------------------------------------------------------*/

template <typename T> struct TIsPODType : TConstBoolean<HAS_TRIVIAL_DESTRUCTOR(T) || TOr<TIsEnum<T>, TIsArithmetic<T>, TIsPointer<T>>::Value> {};

IMPLEMENT_VALUE_METHOD(IsPODType)

/*----------------------------------------------------------------------------
         TIsTriviallyDestructible.
----------------------------------------------------------------------------*/

namespace Engine_Private
{
   template <typename T, bool bIsTriviallyTriviallyDestructible = IS_ENUM(T)> struct TIsTriviallyDestructibleImpl : TConstBoolean<true> {};
   template <typename T> struct TIsTriviallyDestructibleImpl<T, false> : TConstBoolean<HAS_TRIVIAL_DESTRUCTOR(T)> {};
}

template <typename T> struct TIsTriviallyDestructible : Engine_Private::TIsTriviallyDestructibleImpl<T> {};

IMPLEMENT_VALUE_METHOD(IsTriviallyDestructible)

/*----------------------------------------------------------------------------
         TIsTriviallyCopyAssignable.
----------------------------------------------------------------------------*/

template <typename T> struct TIsTriviallyCopyAssignable : TConstBoolean<IsPODType<T> || HAS_TRIVIAL_ASSIGN(T)> {};

IMPLEMENT_VALUE_METHOD(IsTriviallyCopyAssignable)

/*----------------------------------------------------------------------------
         TIsTriviallyCopyConstructible.
----------------------------------------------------------------------------*/

template <typename T> struct TIsTriviallyCopyConstructible : TConstBoolean<IsPODType<T> || HAS_TRIVIAL_COPY(T)> {};

IMPLEMENT_VALUE_METHOD(IsTriviallyCopyConstructible)

/*----------------------------------------------------------------------------
			IsCompound.
----------------------------------------------------------------------------*/

template<typename T> struct TIsCompound : TNot<TIsFundamental<T>> { };

IMPLEMENT_VALUE_METHOD(IsCompound)

/*----------------------------------------------------------------------------
			TIsScalar.
----------------------------------------------------------------------------*/

template<typename T> struct TIsScalar : TOr<TIsArithmetic<T>, TIsEnum<T>, TIsPointer<T>, TIsNullPointer<T>, TIsMemberPointer<T>> { };

IMPLEMENT_VALUE_METHOD(IsScalar)

/*----------------------------------------------------------------------------
			TIsObject.
----------------------------------------------------------------------------*/

template<typename T> struct TIsObject : TOr<TIsScalar<T>, TIsArray<T>, TIsUnion<T>, TIsStruct<T>> { };

IMPLEMENT_VALUE_METHOD(IsObject)

/*----------------------------------------------------------------------------
			TIsZeroConstructType.
----------------------------------------------------------------------------*/

template<typename T> struct TIsZeroConstructType : TOr<TIsEnum<T>, TIsArithmetic<T>, TIsPointer<T>> {};

IMPLEMENT_VALUE_METHOD(IsZeroConstructorType)

/*----------------------------------------------------------------------------
			TExtend.
----------------------------------------------------------------------------*/

template<typename T, unsigned Size = 0> struct TExtent : TIntegralConst<uint32, 0> { };
template<typename T> struct TExtent<T[], 0> :TIntegralConst<uint32, 0> { };
template<typename T, unsigned Size> struct TExtent<T[], Size> : TExtent<T, Size - 1> { };
template<typename T, uint32 I> struct TExtent<T[I], 0> : TIntegralConst<uint32, I> { };
template<typename T, uint32 I, uint32 Size> struct TExtent<T[I], Size> : TExtent<T, Size - 1> { };

/*----------------------------------------------------------------------------
			TRank.
----------------------------------------------------------------------------*/

template<typename T> struct TRank : TIntegralConst<uint32, 0> {};
template<typename T> struct TRank<T[]> : TIntegralConst<uint32, TRank<T>::Value + 1> {};
template<typename T, uint32 Size> struct TRank<T[Size]> : TIntegralConst<uint32, TRank<T>::Value + 1> {};

/*----------------------------------------------------------------------------
			TArrayDimensionSizes.
----------------------------------------------------------------------------*/

namespace Engine_Private
{
	template<typename T, int Rank>
	struct TArrayDimensionSizesHelper
	{
		CONSTEXPR static uint32* Dimensions = nullptr;
	};

	#define _Ext(Index) TExtent<T, Index>::Value

	#define Expose_TArrayDimensionSizesHelper(Rank, ...) \
	   template<typename T> \
	   struct TArrayDimensionSizesHelper<T, Rank> \
	   { \
		   CONSTEXPR static uint32 Dimensions[] = { __VA_ARGS__ }; \
         CONSTEXPR static uint32 DimensionsLength = Rank; \
	   }; \

   Expose_TArrayDimensionSizesHelper(1, _Ext(0))
   Expose_TArrayDimensionSizesHelper(2, _Ext(0), _Ext(1))
   Expose_TArrayDimensionSizesHelper(3, _Ext(0), _Ext(1), _Ext(2))
   Expose_TArrayDimensionSizesHelper(4, _Ext(0), _Ext(1), _Ext(2), _Ext(3))
   Expose_TArrayDimensionSizesHelper(5, _Ext(0), _Ext(1), _Ext(2), _Ext(3), _Ext(4))
   Expose_TArrayDimensionSizesHelper(6, _Ext(0), _Ext(1), _Ext(2), _Ext(3), _Ext(4), _Ext(5))
   Expose_TArrayDimensionSizesHelper(7, _Ext(0), _Ext(1), _Ext(2), _Ext(3), _Ext(4), _Ext(5), _Ext(6))
   Expose_TArrayDimensionSizesHelper(8, _Ext(0), _Ext(1), _Ext(2), _Ext(3), _Ext(4), _Ext(5), _Ext(6), _Ext(7))
   Expose_TArrayDimensionSizesHelper(9, _Ext(0), _Ext(1), _Ext(2), _Ext(3), _Ext(4), _Ext(5), _Ext(6), _Ext(7), _Ext(8))

	#undef Expose_TArrayDimensionSizesHelper
   #undef _Ext
}

template<typename T> struct TArrayDimensionSizes : Engine_Private::TArrayDimensionSizesHelper<T, TRank<T>::Value> { };

/*----------------------------------------------------------------------------
			TIsBaseOf.
----------------------------------------------------------------------------*/

template<typename Base, typename Derived>
struct TIsBaseOf
{
private:

	static uint32 Test(Base*);
	static uint32 Test(const Base*);
	static uint8 Test(...);

public:

	CONSTEXPR static bool Value = sizeof(Test((Derived*)nullptr)) == sizeof(uint32);
};

template<typename Base, typename Derived>
CONSTEXPR bool IsBaseOf = TIsBaseOf<Base, Derived>::Value;

/*----------------------------------------------------------------------------
			TChangeSign.
----------------------------------------------------------------------------*/

template<typename T>
struct TChangeSign
{
	using Signed = 
		ConditionalType<IsSame<T, signed char> || IsSame<T, unsigned char>, signed char,
		ConditionalType<IsSame<T, signed short> || IsSame<T, unsigned short>, signed short,
		ConditionalType<IsSame<T, signed int> || IsSame<T, unsigned int>, signed int,
		ConditionalType<IsSame<T, signed int> || IsSame<T, unsigned int>, signed int,
		ConditionalType<IsSame<T, signed long> || IsSame<T, unsigned long>,signed long,
		ConditionalType<IsSame<T, signed long long> || IsSame<T, unsigned long long>, signed long long,
		ConditionalType<sizeof(T) == sizeof(signed char), signed char,
		ConditionalType<sizeof(T) == sizeof(signed short),	signed short,
		ConditionalType<sizeof(T) == sizeof(signed int), signed int,
		ConditionalType<sizeof(T) == sizeof(signed long), signed long,
		ConditionalType<sizeof(T) == sizeof(signed long long), signed long long,
		void>>>>>>>>>>>;

	using Unsigned =
      ConditionalType<IsSame<T, signed char> || IsSame<T, unsigned char>, unsigned char,
      ConditionalType<IsSame<T, signed short> || IsSame<T, unsigned short>, unsigned short,
      ConditionalType<IsSame<T, signed int> || IsSame<T, unsigned int>, unsigned int,
      ConditionalType<IsSame<T, signed int> || IsSame<T, unsigned int>, unsigned int,
      ConditionalType<IsSame<T, signed long> || IsSame<T, unsigned long>, unsigned long,
      ConditionalType<IsSame<T, signed long long> || IsSame<T, unsigned long long>, unsigned long long,
      ConditionalType<sizeof(T) == sizeof(signed char), unsigned char,
      ConditionalType<sizeof(T) == sizeof(signed short), unsigned short,
      ConditionalType<sizeof(T) == sizeof(signed int), unsigned int,
      ConditionalType<sizeof(T) == sizeof(signed long), unsigned long,
      ConditionalType<sizeof(T) == sizeof(signed long long), unsigned long long,
      void>>>>>>>>>>>;
};

template<typename T>
struct TChangeSign<const T>
{
	using Signed = const typename TChangeSign<T>::Signed;
	using Unsigned = const typename TChangeSign<T>::Unsigned;
};

template<typename T>
struct TChangeSign<volatile T>
{
	using Signed = volatile typename TChangeSign<T>::Signed;
	using Unsigned = volatile typename TChangeSign<T>::Unsigned;
};

template<typename T>
struct TChangeSign<const volatile T>
{
	using Signed = const volatile typename TChangeSign<T>::Signed;
	using Unsigned = const volatile typename TChangeSign<T>::Unsigned;
};

/*----------------------------------------------------------------------------
			TMakeSigned.
----------------------------------------------------------------------------*/

template<typename T> struct TMakeSigned : Engine_Private::TType<typename TChangeSign<T>::Signed> { };

/*----------------------------------------------------------------------------
			TMakeUnsigned.
----------------------------------------------------------------------------*/

template<typename T> struct TMakeUnsigned : Engine_Private::TType<typename TChangeSign<T>::Unsigned> { };

/*----------------------------------------------------------------------------
			TMaxSizeOf.
----------------------------------------------------------------------------*/

template<typename...> struct TMaxSizeof { };
template<> struct TMaxSizeof<> : TIntegralConst<uint32, 0> { };
template<typename T, typename... TRest> struct TMaxSizeof<T, TRest...> 
	: TIntegralConst<uint32, TMaxSizeof<TRest...>::Value ? sizeof(T) : TMaxSizeof<TRest...>::Value> { };

/*----------------------------------------------------------------------------
         TIntegralLimits.
----------------------------------------------------------------------------*/

#define Expose_TIntegralLimitsHelper(Bytes, IsSigned, MinValue, MaxValue) \
   template<typename T> struct TIntegralLimitsHelper<T, Bytes, IsSigned> \
   { \
      CONSTEXPR static T Min = MinValue, Max = MaxValue; \
   }; 

namespace Engine_Private
{ 
   template<typename T, uint32 Bytes, bool IsSigned> struct TIntegralLimitsHelper;

   Expose_TIntegralLimitsHelper(1, false, 0, 0xFF)
   Expose_TIntegralLimitsHelper(1, true, -0x80, 0x7F)

   Expose_TIntegralLimitsHelper(2, false, 0, 0xFFFF)
   Expose_TIntegralLimitsHelper(2, true, -0x8000, 0x7FFF)

   Expose_TIntegralLimitsHelper(4, false, 0, 0xFFFFFFFF)
   Expose_TIntegralLimitsHelper(4, true, -0x80000000, 0x7FFFFFFF)

   Expose_TIntegralLimitsHelper(8, false, 0, 0xFFFFFFFFFFFFFFFF)
   Expose_TIntegralLimitsHelper(8, true, -0x8000000000000000, 0x7FFFFFFFFFFFFFFF)
}

template<typename T> struct TIntegralLimits : Engine_Private::TIntegralLimitsHelper<T, sizeof(T), TIsSigned<T>::Value>
{
   static_assert(IsIntegral<T>, "T has to be integral.");
};

template<> struct TIntegralLimits<float>
{
   CONSTEXPR static float Min = 1.175494351E-38F, Max = 3.402823466E38F;
};
template<> struct TIntegralLimits<double>
{
   CONSTEXPR static double Min = 2.2250738585072014E-308, Max = 1.7976931348623158E308;
};

template<typename T> struct TIntegralLimits<const T> : TIntegralLimits<T> { };
template<typename T> struct TIntegralLimits<volatile T> : TIntegralLimits<T> { };
template<> struct TIntegralLimits<long double> : TIntegralLimits<double> { };

#undef Implement_TIntegralLimitsHelperSpecialization

/*----------------------------------------------------------------------------
			TNameOf.
----------------------------------------------------------------------------*/

template<typename T>
struct TNameOf
{
	FORCEINLINE static const TCHAR* GetName()
	{
		return TEXT("Unknown");
	}
};

#define Expose_TNameOf(Type) \
template<> \
struct TNameOf<Type> \
{ \
	FORCEINLINE static const TCHAR (&GetName())[sizeof(PREPROCESSOR_TO_STRING(Type))] \
	{ \
		static const TCHAR Specifier[sizeof(PREPROCESSOR_TO_STRING(Type))] = TEXT(PREPROCESSOR_TO_STRING(Type)); \
		return Specifier; \
	} \
}; \

Expose_TNameOf(uint8)
Expose_TNameOf(uint16)
Expose_TNameOf(uint32)
Expose_TNameOf(uint64)
Expose_TNameOf(int8)
Expose_TNameOf(int16)
Expose_TNameOf(int32)
Expose_TNameOf(int64)
Expose_TNameOf(float)
Expose_TNameOf(double)
Expose_TNameOf(bool)
Expose_TNameOf(void)

/*----------------------------------------------------------------------------
			TFormatSpecifier.
----------------------------------------------------------------------------*/

template<typename T>
struct TFormatSpecifier
{
	FORCEINLINE static const TCHAR* GetFormatSpecifier()
	{
		static_assert(TIsArithmetic<T>::Value, "T must be a arithmetic type.");
		return TEXT("Unknown");
	}
};

#define Expose_TFormatSpecifier(Type, Format) \
template<> \
struct TFormatSpecifier<Type> \
{ \
	FORCEINLINE static const TCHAR (&GetFormatSpecifier())[sizeof(Format)] \
	{ \
		static const TCHAR Specifier[sizeof(Format)] = TEXT(Format); \
		return Specifier; \
	} \
}; \

Expose_TFormatSpecifier(WIDECHAR, "%lc")
Expose_TFormatSpecifier(ANSICHAR, "%c")
Expose_TFormatSpecifier(bool, "%i")
Expose_TFormatSpecifier(uint8, "%u")
Expose_TFormatSpecifier(uint16, "%u")
Expose_TFormatSpecifier(uint32, "%u")
Expose_TFormatSpecifier(uint64, "%llu")
Expose_TFormatSpecifier(int8, "%d")
Expose_TFormatSpecifier(int16, "%d")
Expose_TFormatSpecifier(int32, "%d")
Expose_TFormatSpecifier(int64, "%lld")
Expose_TFormatSpecifier(float, "%f")
Expose_TFormatSpecifier(double, "%f")
Expose_TFormatSpecifier(long double, "%f")

#undef Expose_TFormatSpecifier 

/*----------------------------------------------------------------------------
			Remover definição das macros utilizadas.
----------------------------------------------------------------------------*/

#undef IS_ABSTRACT
#undef IS_ENUM
#undef IS_UNION
#undef IS_POD
#undef HAS_TRIVIAL_DESTRUCTOR
#undef HAS_TRIVIAL_ASSIGN
#undef HAS_TRIVIAL_COPY
#undef IMPLEMENT_USING_TYPE
#undef IMPLEMENT_VALUE_METHOD