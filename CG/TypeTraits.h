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

#include "Core.h"

/* ---------------- SelectPlatformType ---------------- */

template<typename T32Bits, typename T64Bits, int PointerSize> struct TSelectPlatformTypeHelper { };

/** Specializations */
template<typename T32Bits, typename T64Bits>
struct TSelectPlatformTypeHelper<T32Bits, T64Bits, 8>
{
	typedef T64Bits Type;
};

template<typename T32Bits, typename T64Bits>
struct TSelectPlatformTypeHelper<T32Bits, T64Bits, 4>
{
	typedef T32Bits Type;
};

template<typename T32Bits, typename T64Bits> struct TSelectPlatformType : TSelectPlatformTypeHelper<T32Bits, T64Bits, sizeof(void*)> { };

/* ---------------- ConstBoolean ---------------- */

template<bool Boolean>
struct TConstBoolean
{
	static constexpr bool Value = Boolean;

	constexpr bool operator()()
	{
		return Value;
	}

	constexpr operator bool()
	{
		return Value;
	}
};

struct FTrue : TConstBoolean<true> { };
struct FFalse : TConstBoolean<false> { };

/* ---------------- EnableIf ---------------- */

template<bool bCondition, typename T> struct TEnableIf { };

/** Specailization */
template<typename T>
struct TEnableIf<true, T>
{
	typedef T Type;
};

/* ---------------- RemoveConst ---------------- */

template<typename T>
struct TRemoveConst
{
	typedef T Type;
};

/** Specialization */
template<typename T> struct TRemoveConst<const T> : TRemoveConst<T> { };

/* ---------------- RemoveVolatite ---------------- */

template<typename T>
struct TRemoveVolatite
{
	typedef T Type;
};

/** Specailization */
template<typename T>
struct TRemoveVolatite<volatile T>
{
	typedef T Type;
};

/* ---------------- RemoveConstAndVolatite ---------------- */

template<typename T>
struct TRemoveConstAndVolatite
{
	typedef typename TRemoveVolatite<typename TRemoveConst<T>::Type>::Type Type;
};

/* ---------------- RemovePointer ---------------- */

template<typename T>
struct TRemovePointer
{
	typedef T Type;
};

/** Specailization */
template<typename T>
struct TRemovePointer<T*>
{
	typedef T Type;
};

/* ---------------- RemoveReference ---------------- */

template<typename T>
struct TRemoveReference
{
	typedef T Type;
};

/** Specailization */
template<typename T>
struct TRemoveReference<T&>
{
	typedef T Type;
};

/* ---------------- RemovePointerAndReference ---------------- */

template<typename T>
struct TRemovePointerAndReference
{
	typedef typename TRemovePointer<typename TRemoveReference<T>::Type>::Type Type;
};

/* ---------------- RemovePointerAndReference ---------------- */

template<typename T>
struct TRemoveArray
{
	typedef T Type;
};

/** Specailization */
template<typename T>
struct TRemoveArray<T[]>
{
	typedef T Type;
};

template<typename T, int Size>
struct TRemoveArray<T[Size]>
{
	typedef T Type;
};

/* ---------------- MakeUnsigned ---------------- */

template<typename T>
struct TMakeUnsignedHelper
{
	typedef T Type;
};


template<typename T> struct TMakeUnsigned : TMakeUnsignedHelper<T> { };

/* ---------------- IsSame ---------------- */

template<typename T, typename U> struct TIsSame : FFalse { };

/** Specailization */
template<typename T> struct TIsSame<T, T> : FTrue { };

/* ---------------- IsIntegral ---------------- */

template<typename T>  struct TIsIntegralHelper : FFalse { };

/** Specailization */
template<> struct TIsIntegralHelper<bool> : FTrue { };
template<> struct TIsIntegralHelper<char> : FTrue { };
template<> struct TIsIntegralHelper<char16_t> : FTrue { };
template<> struct TIsIntegralHelper<char32_t> : FTrue { };
template<> struct TIsIntegralHelper<wchar_t> : FTrue { };
template<> struct TIsIntegralHelper<short> : FTrue { };
template<> struct TIsIntegralHelper<int> : FTrue { };
template<> struct TIsIntegralHelper<long> : FTrue { };
template<> struct TIsIntegralHelper<long long> : FTrue { };


template<typename T> struct TIsIntegral : TIsIntegralHelper<typename TRemoveConstAndVolatite<T>::Type> { };

/* ---------------- IsFloatingPoint ---------------- */

template<typename T> struct TIsFloatingPointHelper : FFalse { };

/** Specailization */
template<> struct TIsFloatingPointHelper<float> : FTrue { };
template<> struct TIsFloatingPointHelper<double> : FTrue { };
template<> struct TIsFloatingPointHelper<long double> : FTrue { };


template<typename T> struct TIsFloatingPoint : TIsFloatingPointHelper<typename TRemoveConstAndVolatite<T>::Type> { };

/* ---------------- IsFunction ---------------- */

template<typename T> struct TIsFunction : FFalse { };

/** Specailization */
template<typename Return, typename... Arguments> struct TIsFunction<Return(Arguments...)> : FTrue { };
template<typename Return, typename... Arguments> struct TIsFunction<Return(Arguments...) const> : FTrue { };
template<typename Return, typename... Arguments> struct TIsFunction<Return(Arguments...) volatile> : FTrue { };
template<typename Return, typename... Arguments> struct TIsFunction<Return(Arguments...) const volatile> : FTrue { };
template<typename Return, typename... Arguments> struct TIsFunction<Return(Arguments...) &> : FTrue { };
template<typename Return, typename... Arguments> struct TIsFunction<Return(Arguments...) const &> : FTrue { };
template<typename Return, typename... Arguments> struct TIsFunction<Return(Arguments...) volatile &> : FTrue { };
template<typename Return, typename... Arguments> struct TIsFunction<Return(Arguments...) const volatile &> : FTrue { };
template<typename Return, typename... Arguments> struct TIsFunction<Return(Arguments...) && > : FTrue { };
template<typename Return, typename... Arguments> struct TIsFunction<Return(Arguments...) const &&> : FTrue { };
template<typename Return, typename... Arguments> struct TIsFunction<Return(Arguments...) volatile &&> : FTrue { };
template<typename Return, typename... Arguments> struct TIsFunction<Return(Arguments...) const volatile &&> : FTrue { };

/* ---------------- IsMemberFunctionPointer ---------------- */

template<typename T> struct TIsMemberFunctionPointerHelper : FFalse { };

/** Specailization */
template<typename T, typename U> struct TIsMemberFunctionPointerHelper<T U::*> : TIsFunction<T> { };


template<typename T> struct TIsMemberFunctionPointer : TIsMemberFunctionPointerHelper<typename TRemoveConstAndVolatite<T>::Type> { };

/* ---------------- IsArray ---------------- */

template<typename T> struct TIsArray : FFalse { };

/** Specailization */
template<typename T> struct TIsArray<T[]> : FTrue { };
template<typename T, int Size> struct TIsArray<T[Size]> : FTrue { };

/* ---------------- IsVoid ---------------- */

template<typename T> struct TIsVoidHelper : FFalse { };

/** Specializations */
template<>  struct TIsVoidHelper<void> : FTrue { };


template<typename T> struct TIsVoid : TIsVoidHelper<typename TRemoveConstAndVolatite<T>::Type> { };

/* ---------------- IsNullPointer ---------------- */

template<typename T> struct TIsNullPointerHelper : FFalse { };

/** Specializations */
template<> struct TIsNullPointerHelper<decltype(nullptr)> : FTrue { };


template<typename T> struct TIsNullPointer : TIsNullPointerHelper<typename TRemoveConstAndVolatite<T>::Type> { };

/* ---------------- IsPointer ---------------- */

template<typename T> struct TIsPointer : FFalse { };

/** Specializations */
template<typename T> struct TIsPointer<T*> : FTrue { };

/* ---------------- IsMemberPointer ---------------- */

template<typename T> struct TIsMemberPointerHelper : FFalse { };

/** Specializations */
template<typename T, typename U> struct TIsMemberPointerHelper<T U::*> : FTrue { };


template<typename T> struct TIsMemberPointer : TIsMemberPointerHelper<typename TRemoveConstAndVolatite<T>::Type> { };

/* ---------------- IsReference ---------------- */

template<typename T> struct TIsReference : FFalse { };

/** Specializations */
template<typename T> struct TIsReference<T&> : FTrue { };

/* ---------------- IsConst ---------------- */

template<typename T> struct TIsConstHelper : FFalse { };

/** Specializations */
template<typename T> struct TIsConstHelper<const T> : FTrue { };


template<typename T> struct TIsConst : TIsConstHelper<typename TRemovePointerAndReference<typename TRemoveArray<T>::Type>::Type> { };

/* ---------------- IsVolatile ---------------- */

template<typename T> struct TIsVolatileHelper : FFalse { };

/** Specializations */
template<typename T> struct TIsVolatileHelper<volatile T> : FTrue { };


template<typename T> struct TIsVolatile : TIsVolatileHelper<typename TRemovePointerAndReference<typename TRemoveArray<T>::Type>::Type> { };

/* ---------------- IsUnion ---------------- */

template<typename T> struct TIsUnion : TConstBoolean<__is_union(T)> { };

/* ---------------- IsEnum ---------------- */

template<typename T> struct TIsEnum : TConstBoolean<__is_enum(T)> { };

/* ---------------- Istypename ---------------- */

namespace Detail
{
	template <typename T>
	char Test(int T::*);

	struct TwoBytes {
		char Bytes[2];
	};
	template <typename T>
	TwoBytes Test(...);
}

template<typename T>  struct TIstypename : TConstBoolean<sizeof(Detail::Test<T>(0)) == 1
	&& !TIsUnion<T>::Value> { };

/* ---------------- IsArithmetic ---------------- */

template<typename T> struct TIsArithmetic : TConstBoolean<TIsIntegral<T>::Value
	|| TIsFloatingPoint<T>::Value> { };

/* ---------------- IsUnsigned ---------------- */

template<typename T> struct TIsUnsigned : TConstBoolean<TIsArithmetic<T>::Value
	&& T(0) < T(-1)> { };

/* ---------------- IsSigned ---------------- */

template<typename T> struct TIsSigned : TConstBoolean<TIsArithmetic<T>::Value
	&& T(-1) < T(0)> { };

/* ---------------- IsFundamental ---------------- */

template<typename T> struct TIsFundamental : TConstBoolean<TIsArithmetic<T>::Value
	|| TIsVoid<T>::Value
	|| TIsSame<std::nullptr_t, T>::Value> { };

/* ---------------- IsCompound ---------------- */

template<typename T> struct IsCompound : TConstBoolean<!TIsFundamental<T>::Value> { };

/* ---------------- IsScalar ---------------- */

template<typename T> struct TIsScalar : TConstBoolean<TIsArithmetic<T>::Value
	|| TIsEnum<T>::Value
	|| TIsPointer<T>::Value
	|| TIsNullPointer<T>::Value
	|| TIsMemberPointer<T>::Value> { };

/* ---------------- IsObject ---------------- */

template<typename T> struct TIsObject : TConstBoolean<TIsScalar<T>::Value
	|| TIsArray<T>::Value
	|| TIsUnion<T>::Value
	|| TIstypename<T>::Value> { };

/* ---------------- IsNative ---------------- */

template<typename T> struct TIsNative : FTrue { };

/* ---------------- IntegralConst ---------------- */

template<typename T, T U>
struct TIntegralConst
{
	static_assert(!TIsIntegral<T>::Value, "T must be integral.");

	static constexpr T Value = U;
};

/* ---------------- Extend ---------------- */

template<class T, unsigned Size = 0>
struct TExtent : TIntegralConst<uint32_t, 0> { };

/** Specializations */
template<class T> struct TExtent<T[], 0> :TIntegralConst<uint32_t, 0> { };
template<class T, unsigned Size> struct TExtent<T[], Size> : TExtent<T, Size - 1> { };
template<class T, uint32_t I> struct TExtent<T[I], 0> : TIntegralConst<uint32_t, I> { };
template<class T, uint32_t I, unsigned Size> struct TExtent<T[I], Size> : TExtent<T, Size - 1> { };

/* ---------------- Rank ---------------- */

template<class T> struct TRank : public TIntegralConst<uint32_t, 0> {};

/** Specializations */
template<class T> struct TRank<T[]> : public TIntegralConst<uint32_t, TRank<T>::Value + 1> {};
template<class T, uint32_t Size> struct TRank<T[Size]> : public TIntegralConst<uint32_t, TRank<T>::Value + 1> {};

/* ---------------- DimensionsSize ---------------- */

/** Ajudantes */
#define __El(Index)		TExtent<T, Index>::Value
#define __Value			static constexpr const uint32_t Value[]
#define __Class			template<typename T> struct TArrayDimensionSizesHelper

template<typename T, int Rank>
struct TArrayDimensionSizesHelper
{
	static constexpr const uint32_t* Value = nullptr;
};

/** Specializations */
__Class<T, 1> { __Value = { __El(0) }; };
__Class<T, 2> { __Value = { __El(0), __El(1) }; };
__Class<T, 3> { __Value = { __El(0), __El(1), __El(2) }; };
__Class<T, 4> { __Value = { __El(0), __El(1), __El(2), __El(3) }; };
__Class<T, 5> { __Value = { __El(0), __El(1), __El(2), __El(3), __El(4) }; };
__Class<T, 6> { __Value = { __El(0), __El(1), __El(2), __El(3), __El(4), __El(5) }; };
__Class<T, 7> { __Value = { __El(0), __El(1), __El(2), __El(3), __El(4), __El(5), __El(6) }; };
__Class<T, 8> { __Value = { __El(0), __El(1), __El(2), __El(3), __El(4), __El(5), __El(6).__El(7) }; };

#undef __El
#undef __Value
#undef __Class


template<typename T> struct TArrayDimensionSizes : TArrayDimensionSizesHelper<T, TRank<T>::Value> { };

/* ---------------- IsBaseOf ---------------- */

typedef char(&Yes)[1];
typedef char(&No)[2];

template <typename Base, typename Derived>
struct THost
{
	operator Base*() const;
	operator Derived*();
};

template <typename Base, typename Derived>
struct TIsBaseOf
{
	template <typename T>
	static Yes Check(Derived*, T);
	static No Check(Base*, int);

	static constexpr bool Value = sizeof(Check(THost<Base, Derived>(), int())) == sizeof(Yes);
};
