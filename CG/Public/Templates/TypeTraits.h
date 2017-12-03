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
			Utilitário(s) para os traits.
----------------------------------------------------------------------------*/

namespace Engine_Private
{
	// Apenas pra evitar um pouco de repetição código
	template<typename T>
	struct TType
	{
		using Type = T;
	};
}

/*----------------------------------------------------------------------------
			Macros para os type traits intrínsecos do compilador.
----------------------------------------------------------------------------*/

#define IS_ENUM(T) __is_enum(T)
#define IS_UNION(T) __is_union(T)
#define IS_ABSTRACT(T) __is_abstract(T)

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

/*----------------------------------------------------------------------------
			TSelectPlatformType.
----------------------------------------------------------------------------*/

template<typename T32Bits, typename T64Bits> struct TSelectPlatformType : TConditional<sizeof(void*) == 4, T32Bits, T64Bits> { };

/*----------------------------------------------------------------------------
			TConstBoolean, TBooleanTrue, TBooleanFalse.
----------------------------------------------------------------------------*/

template<bool Predicate> struct TConstBoolean : TIntegralConst<bool, Predicate> { };

struct TBooleanTrue : TConstBoolean<true> { };
struct TBooleanFalse : TConstBoolean<false> { };

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

template<bool Predicate, typename T> struct TEnableIf { };
template<typename T> struct TEnableIf<true, T> : Engine_Private::TType<T> { };
template<bool Predicate> struct TEnableIf<Predicate, void> : Engine_Private::TType<void> { };

/*----------------------------------------------------------------------------
			TRemoveConst.
----------------------------------------------------------------------------*/

template<typename T> struct TRemoveConst : Engine_Private::TType<T> { };
template<typename T> struct TRemoveConst<const T> : TRemoveConst<T> { };

/** Remover const de um tipo */
#define REMOVE_CONST(T) typename TRemoveConst<T>::Type

/*----------------------------------------------------------------------------
			TRemoveVolatile.
----------------------------------------------------------------------------*/

template<typename T> struct TRemoveVolatile : Engine_Private::TType<T> { };
template<typename T>  struct TRemoveVolatile<volatile T> : TRemoveVolatile<T> { };

/** Remover volatile de um tipo */
#define REMOVE_VOLATILE(T) typename TRemoveVolatile<T>::Type

/*----------------------------------------------------------------------------
			TRemoveConstAndVolatite.
----------------------------------------------------------------------------*/

template<typename T> struct TRemoveConstAndVolatite : Engine_Private::TType<REMOVE_VOLATILE(REMOVE_CONST(T))> { };

/** Remover const e volatile de um tipo */
#define REMOVE_CV(T) typename TRemoveConstAndVolatite<T>::Type

/*----------------------------------------------------------------------------
			TRemovePointer.
----------------------------------------------------------------------------*/

template<typename T> struct TRemovePointer : Engine_Private::TType<T> { };
template<typename T> struct TRemovePointer<T*> : TRemovePointer<T> { };

/** Remover pointeiro de um tipo */
#define REMOVE_PTR(T) typename TRemovePointer<T>::Type

/*----------------------------------------------------------------------------
			TRemoveReference.
----------------------------------------------------------------------------*/

template<typename T> struct TRemoveReference : Engine_Private::TType<T> { };
template<typename T> struct TRemoveReference<T&> : TRemoveReference<T> {};

/** Remover a referência de um tipo */
#define REMOVE_REF(T) typename TRemoveReference<T>::Type

/*----------------------------------------------------------------------------
			TRemovePointerAndReference.
----------------------------------------------------------------------------*/

template<typename T> struct TRemovePointerAndReference : Engine_Private::TType<REMOVE_PTR(REMOVE_REF(T))> { };

/** Remover pointeiro e referência de um tipo */
#define REMOVE_RP(T) typename	TRemovePointerAndReference<T>::Type

/*----------------------------------------------------------------------------
			TRemoveExtend.
----------------------------------------------------------------------------*/

template<typename T> struct TRemoveExtend : Engine_Private::TType<T> { };
template<typename T> struct TRemoveExtend<T[]> : TRemoveExtend<T> { };
template<typename T, uint32 Size> struct TRemoveExtend<T[Size]> : TRemoveExtend<T> { };

/** Remove array de um tipo */
#define REMOVE_ARRAY(T) typename TRemoveExtend<T>::Type

/*----------------------------------------------------------------------------
			TRemovePointerReferenceAndArray.
----------------------------------------------------------------------------*/

template<typename T> struct TRemovePointerReferenceAndArray : Engine_Private::TType<REMOVE_ARRAY(REMOVE_RP(T))> { };

/** Remover pointeiro, referência e array de um tipo */
#define REMOVE_RPA(T) typename TRemovePointerReferenceAndArray<T>::Type

/*----------------------------------------------------------------------------
			TIsSame.
----------------------------------------------------------------------------*/

template<typename T, typename U> struct TIsSame : TBooleanFalse { };
template<typename T> struct TIsSame<T, T> : TBooleanTrue { };

/*----------------------------------------------------------------------------
			TIsIntegral.
----------------------------------------------------------------------------*/

namespace Engine_Private
{
	template<typename T> struct TIsIntegralHelper : TBooleanFalse { };

	template<> struct TIsIntegralHelper<bool> : TBooleanTrue { };
	template<> struct TIsIntegralHelper<char> : TBooleanTrue { };
	template<> struct TIsIntegralHelper<char16_t> : TBooleanTrue { };
	template<> struct TIsIntegralHelper<char32_t> : TBooleanTrue { };
	template<> struct TIsIntegralHelper<wchar_t> : TBooleanTrue { };
	template<> struct TIsIntegralHelper<short> : TBooleanTrue { };
	template<> struct TIsIntegralHelper<int> : TBooleanTrue { };
	template<> struct TIsIntegralHelper<long> : TBooleanTrue { };
	template<> struct TIsIntegralHelper<long long> : TBooleanTrue { };
}

template<typename T> struct TIsIntegral : Engine_Private::TIsIntegralHelper<REMOVE_CV(T)> { };

/*----------------------------------------------------------------------------
			TIsFloatingPoint.
----------------------------------------------------------------------------*/

namespace Engine_Private
{
	template<typename T> struct TIsFloatingPointHelper : TBooleanFalse { };

	template<> struct TIsFloatingPointHelper<float> : TBooleanTrue { };
	template<> struct TIsFloatingPointHelper<double> : TBooleanTrue { };
	template<> struct TIsFloatingPointHelper<long double> : TBooleanTrue { };
}

template<typename T> struct TIsFloatingPoint : Engine_Private::TIsFloatingPointHelper<REMOVE_CV(T)> { };

/*----------------------------------------------------------------------------
			TIsFunction.
----------------------------------------------------------------------------*/

template<typename T> struct TIsFunction : TBooleanFalse { };

template<typename Return, typename... Params> struct TIsFunction<Return(Params...)> : TBooleanTrue { };
template<typename Return, typename... Params> struct TIsFunction<Return(Params...) const> : TBooleanTrue { };

/*----------------------------------------------------------------------------
			TIsMemberFunctionPointer.
----------------------------------------------------------------------------*/

namespace Engine_Private
{
	template<typename T> struct TIsMemberFunctionPointerHelper : TBooleanFalse { };
	template<typename T, typename U> struct TIsMemberFunctionPointerHelper<T U::*> : TIsFunction<T> { };
}

template<typename T> struct TIsMemberFunctionPointer : Engine_Private::TIsMemberFunctionPointerHelper<REMOVE_CV(T)> { };

/*----------------------------------------------------------------------------
			TFunction.
----------------------------------------------------------------------------*/

namespace Engine_Private
{
	template<uint32 Size, typename T, typename... Args> 
	struct TGetTypeHelper : TType<typename TGetTypeHelper<Size - 1, Args...>::Type> { };

	template<typename T, typename... Args> 
	struct TGetTypeHelper<0, T, Args...> : TType<T> { };

	template<typename T>
	struct TFunctionHelper
	{
		static_assert(TIsFunction<T>::Value, "T must be a function.");
	};

	template<typename Return, typename... Params>
	struct TFunctionHelper<Return(Params...)>
	{
		using ReturnType = Return;

		CONSTEXPR static bool bIsConst = false;
		CONSTEXPR static uint32 ParametersCount = sizeof...(Params);

		template<uint32 ParamIndex> struct Param : TGetTypeHelper<ParamIndex, Params...> { };
	};

	template<typename Return, typename... Params>
	struct TFunctionHelper<Return(Params...) const> : TFunctionHelper<Return(Params...)>
	{
		CONSTEXPR static bool bIsConst = true;
	};
}

template<typename T> struct TFunction : Engine_Private::TFunctionHelper<T> { };

/*----------------------------------------------------------------------------
			TMemberFunctionPointer.
----------------------------------------------------------------------------*/

template<typename T> struct TMemberFunctionPointer;
template<typename T, typename U> struct TMemberFunctionPointer<T U::*> : TFunction<T> { };

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
   template<typename T> static uint8 Check(Helper<Signature, &FunctionName>*); \
   template<typename T> static uint32 Check(...); \
public: \
   CONSTEXPR static bool Value = sizeof(Check<U>(0)) == sizeof(uint8); \
}; \
WARNING(pop) \

/*----------------------------------------------------------------------------
			THasStaticClass, TGetEditorClass.
----------------------------------------------------------------------------*/

struct LClass;
DECLARE_HAS_MEMBER_FUNCTION(THasStaticClass, T::StaticClass, LClass(*)())
DECLARE_HAS_MEMBER_FUNCTION(TGetEditorClass, T::CustomEditor, LClass(*)())

/*----------------------------------------------------------------------------
			TIsArray.
----------------------------------------------------------------------------*/

template<typename T> struct TIsArray : TBooleanFalse { };
template<typename T> struct TIsArray<T[]> : TBooleanTrue { };
template<typename T, uint32 Size> struct TIsArray<T[Size]> : TBooleanTrue { };

/*----------------------------------------------------------------------------
			TIsVoid.
----------------------------------------------------------------------------*/

namespace Engine_Private
{
	template<typename T> struct TIsVoidHelper : TBooleanFalse { };
	template<> struct TIsVoidHelper<void> : TBooleanTrue { };
}

template<typename T> struct TIsVoid :	Engine_Private::TIsVoidHelper<REMOVE_CV(T)> { };

/*----------------------------------------------------------------------------
			TIsNullPointer.
----------------------------------------------------------------------------*/

namespace Engine_Private
{
	template<typename T> struct TIsNullPointerHelper : TBooleanFalse { };
	template<> struct TIsNullPointerHelper<TYPE_OF_NULLPTR> : TBooleanTrue { };
}

template<typename T> struct TIsNullPointer : Engine_Private::TIsNullPointerHelper<REMOVE_CV(T)> { };

/*----------------------------------------------------------------------------
			TIsPointer.
----------------------------------------------------------------------------*/

template<typename T> struct TIsPointer : TBooleanFalse { };
template<typename T> struct TIsPointer<T*> : TBooleanTrue { };

/*----------------------------------------------------------------------------
			TIsMemberPointer.
----------------------------------------------------------------------------*/

namespace Engine_Private
{
	template<typename T> struct TIsMemberPointerHelper : TBooleanFalse { };
	template<typename T, typename U> struct TIsMemberPointerHelper<T U::*> : TBooleanTrue { };
}

template<typename T> struct TIsMemberPointer : Engine_Private::TIsMemberPointerHelper<REMOVE_CV(T)> { };

/*----------------------------------------------------------------------------
			TIsReference.
----------------------------------------------------------------------------*/

template<typename T> struct TIsReference : TBooleanFalse { };
template<typename T> struct TIsReference<T&> : TBooleanTrue { };

/*----------------------------------------------------------------------------
			TIsConst.
----------------------------------------------------------------------------*/

namespace Engine_Private
{
	template<typename T> struct TIsConstHelper : TBooleanFalse { };
	template<typename T> struct TIsConstHelper<const T> : TBooleanTrue { };
}

template<typename T> struct TIsConst : Engine_Private::TIsConstHelper<REMOVE_RPA(T)> { };

/*----------------------------------------------------------------------------
			TIsVolatile.
----------------------------------------------------------------------------*/

namespace Engine_Private
{
	template<typename T> struct TIsVolatileHelper : TBooleanFalse { };
	template<typename T> struct TIsVolatileHelper<volatile T> : TBooleanTrue { };
}

template<typename T> struct TIsVolatile : Engine_Private::TIsVolatileHelper<REMOVE_RPA(T)> { };

/*----------------------------------------------------------------------------
			TIsUnion.
----------------------------------------------------------------------------*/

template<typename T> struct TIsUnion : TConstBoolean<IS_UNION(T)> { };

/*----------------------------------------------------------------------------
			TIsEnum.
----------------------------------------------------------------------------*/

template<typename T> struct TIsEnum : TConstBoolean<IS_ENUM(T)> { };

/*----------------------------------------------------------------------------
			TIsAbstract.
----------------------------------------------------------------------------*/

template <typename T> struct TIsAbstract : TConstBoolean<IS_ABSTRACT(T)> {};

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

	CONSTEXPR static bool Value = sizeof(Test<T>(0)) == sizeof(uint32) && !TIsUnion<T>::Value;
};

/*----------------------------------------------------------------------------
			TIsArithmetic.
----------------------------------------------------------------------------*/

template<typename T> struct TIsArithmetic : TOr<TIsIntegral<T>, TIsFloatingPoint<T>> { };

/*----------------------------------------------------------------------------
			TIsUnsigned.
----------------------------------------------------------------------------*/

namespace Engine_Private
{
	template<bool, typename T> struct TIsUnsignedHelper : TBooleanFalse { };

	template<typename T> struct TIsUnsignedHelper<true, T> : TConstBoolean<T(0) < T(-1)> { };
}

template<typename T> struct TIsUnsigned : Engine_Private::TIsUnsignedHelper<TIsArithmetic<T>::Value, T> { };

/*----------------------------------------------------------------------------
			TIsSigned.
----------------------------------------------------------------------------*/

template<typename T> struct TIsSigned : TNot<TIsUnsigned<T>> { };

/*----------------------------------------------------------------------------
			IsFundamental.
----------------------------------------------------------------------------*/

template<typename T> struct TIsFundamental : TOr<TIsArithmetic<T>, TIsVoid<T>, TIsSame<TYPE_OF_NULLPTR, T>> { };

/*----------------------------------------------------------------------------
			IsCompound.
----------------------------------------------------------------------------*/

template<typename T> struct IsCompound : TNot<TIsFundamental<T>> { };

/*----------------------------------------------------------------------------
			TIsScalar.
----------------------------------------------------------------------------*/

template<typename T> struct TIsScalar : TOr<TIsArithmetic<T>, TIsEnum<T>, TIsPointer<T>, TIsNullPointer<T>, TIsMemberPointer<T>> { };

/*----------------------------------------------------------------------------
			TIsObject.
----------------------------------------------------------------------------*/

template<typename T> struct TIsObject : TOr<TIsScalar<T>, TIsArray<T>, TIsUnion<T>, TIsStruct<T>> { };

/*----------------------------------------------------------------------------
			TIsZeroConstructType.
----------------------------------------------------------------------------*/

template<typename T> struct TIsZeroConstructType : TOr<TIsEnum<T>, TIsArithmetic<T>, TIsPointer<T>> {};

/*----------------------------------------------------------------------------
			TExtend.
----------------------------------------------------------------------------*/

template<typename T, unsigned Size = 0> struct TExtent : TIntegralConst<uint32, 0> { };
template<typename T> struct TExtent<T[], 0> :TIntegralConst<uint32, 0> { };
template<typename T, unsigned Size> struct TExtent<T[], Size> : TExtent<T, Size - 1> { };
template<typename T, uint32 I> struct TExtent<T[I], 0> : TIntegralConst<uint32, I> { };
template<typename T, uint32 I, unsigned Size> struct TExtent<T[I], Size> : TExtent<T, Size - 1> { };

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

	PUSH_MACRO("E")

	#define E(Index) TExtent<T, Index>::Value

	#define Expose_TArrayDimensionSizesHelper(Rank, ...) \
	template<typename T> \
	struct TArrayDimensionSizesHelper<T, Rank> \
	{ \
		CONSTEXPR static uint32 Dimensions[] = { __VA_ARGS__ }; \
	}; \

	Expose_TArrayDimensionSizesHelper(1, E(0))
	Expose_TArrayDimensionSizesHelper(2, E(0), E(1))
	Expose_TArrayDimensionSizesHelper(3, E(0), E(1), E(2))
	Expose_TArrayDimensionSizesHelper(4, E(0), E(1), E(2), E(3))
	Expose_TArrayDimensionSizesHelper(5, E(0), E(1), E(2), E(3), E(4))
	Expose_TArrayDimensionSizesHelper(6, E(0), E(1), E(2), E(3), E(4), E(5))
	Expose_TArrayDimensionSizesHelper(7, E(0), E(1), E(2), E(3), E(4), E(5), E(6))
	Expose_TArrayDimensionSizesHelper(8, E(0), E(1), E(2), E(3), E(4), E(5), E(6), E(7))
	Expose_TArrayDimensionSizesHelper(9, E(0), E(1), E(2), E(3), E(4), E(5), E(6), E(7), E(8))

	#undef Expose_TArrayDimensionSizesHelper

	POP_MACRO("E")
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

/*----------------------------------------------------------------------------
			TIsDerivedFrom.
----------------------------------------------------------------------------*/

template<typename Derived, typename Base> struct TIsDerivedFrom : TIsBaseOf<Base, Derived> { };

/*----------------------------------------------------------------------------
			TChangeSign.
----------------------------------------------------------------------------*/

template<typename T>
struct TChangeSign
{
	static_assert(TIsIntegral<T>::Value || !TIsSame<T, bool>::Value, "T must be a integral (except bool).");

	using Signed = 
		typename TConditional<TIsSame<T, signed char>::Value || TIsSame<T, unsigned char>::Value, signed char,
		typename TConditional<TIsSame<T, signed short>::Value || TIsSame<T, unsigned short>::Value, signed short,
		typename TConditional<TIsSame<T, signed int>::Value || TIsSame<T, unsigned int>::Value, signed int,
		typename TConditional<TIsSame<T, signed int>::Value || TIsSame<T, unsigned int>::Value, signed int,
		typename TConditional<TIsSame<T, signed long>::Value || TIsSame<T, unsigned long>::Value,	signed long,
		typename TConditional<TIsSame<T, signed long long>::Value || TIsSame<T, unsigned long long>::Value, signed long long,
		typename TConditional<sizeof(T) == sizeof(signed char), signed char,
		typename TConditional<sizeof(T) == sizeof(signed short),	signed short,
		typename TConditional<sizeof(T) == sizeof(signed int), signed int,
		typename TConditional<sizeof(T) == sizeof(signed long), signed long,
		typename TConditional<sizeof(T) == sizeof(signed long long), signed long long,
		void>::Type>::Type>::Type>::Type>::Type>::Type>::Type>::Type>::Type>::Type>::Type;

	using Unsigned =
		typename TConditional<TIsSame<T, signed char>::Value || TIsSame<T, unsigned char>::Value, unsigned char,
		typename TConditional<TIsSame<T, signed short>::Value || TIsSame<T, unsigned short>::Value, unsigned short,
		typename TConditional<TIsSame<T, signed int>::Value || TIsSame<T, unsigned int>::Value, unsigned int,
		typename TConditional<TIsSame<T, signed int>::Value || TIsSame<T, unsigned int>::Value, unsigned int,
		typename TConditional<TIsSame<T, signed long>::Value || TIsSame<T, unsigned long>::Value, unsigned long,
		typename TConditional<TIsSame<T, signed long long>::Value || TIsSame<T, unsigned long long>::Value, unsigned long long,
		typename TConditional<sizeof(T) == sizeof(signed char), unsigned char,
		typename TConditional<sizeof(T) == sizeof(signed short), unsigned short,
		typename TConditional<sizeof(T) == sizeof(signed int), unsigned int,
		typename TConditional<sizeof(T) == sizeof(signed long), unsigned long,
		typename TConditional<sizeof(T) == sizeof(signed long long), unsigned long long,
		void>::Type>::Type>::Type>::Type>::Type>::Type>::Type>::Type>::Type>::Type>::Type;
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