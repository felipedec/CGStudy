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

#include "Templates/TypeTraits.h"

template<typename T>
struct TIsTraits
{
public:

	CONSTEXPR static bool IsConst = TIsConst<T>::Value;
	CONSTEXPR static bool IsVolatile = TIsVolatile<T>::Value;
	CONSTEXPR static bool IsPointer = TIsPointer<T>::Value;
	CONSTEXPR static bool IsReference = TIsReference<T>::Value;
	CONSTEXPR static bool IsAbstract = TIsAbstract<T>::Value;
	CONSTEXPR static bool IsArray = TIsArray<T>::Value;
	CONSTEXPR static bool IsArithmetic = TIsArithmetic<T>::Value;
	CONSTEXPR static bool IsObject = TIsObject<T>::Value;
	CONSTEXPR static bool IsSigned = TIsSigned<T>::Value;
	CONSTEXPR static bool IsVoid = TIsVoid<T>::Value;
	CONSTEXPR static bool IsStruct = TIsStruct<T>::Value;
	CONSTEXPR static bool IsUnion = TIsUnion<T>::Value;
	CONSTEXPR static bool IsEnum = TIsEnum<T>::Value;
	CONSTEXPR static bool IsIntegral = TIsIntegral<T>::Value;
	CONSTEXPR static bool IsFloatingPoint = TIsFloatingPoint<T>::Value;
	CONSTEXPR static bool IsScalar = TIsScalar<T>::Value;
	CONSTEXPR static bool IsFundamental = TIsFundamental<T>::Value;
	CONSTEXPR static bool IsFunction = TIsFunction<T>::Value;
	CONSTEXPR static bool IsMemberFunctionPointer = TIsMemberFunctionPointer<T>::Value;
};
