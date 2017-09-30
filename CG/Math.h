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

#include <cmath> // sin, cos, tan


class FMath
{
private:

	union IntFloatUnion
	{
		int32 Int;
		float Float;

		FORCEINLINE IntFloatUnion(const int32 InInt)
		{
			Int = InInt;
		}

		FORCEINLINE IntFloatUnion(const float InFloat)
		{
			Float = InFloat;
		}
	};

public:

	CONSTEXPR static float Pi = 3.14159265358979f;

	CONSTEXPR static float SmallNumber = 1.e-8f;

	CONSTEXPR static float KindaSmallNumber = 1.e-4f;

	CONSTEXPR static float EulersNumber = 2.71828182845904523536f;

	CONSTEXPR static float InversedPi = 0.31830988618f;

	CONSTEXPR static float HalfPi = 1.57079632679f;

	CONSTEXPR static float Delta = 0.00001f;

	CONSTEXPR static float BigNumber = 3.4e+38f;

public:

	CONSTEXPR static float Rad2Deg = (360 / (Pi * 2));

	CONSTEXPR static float Deg2Rad = ((Pi * 2) / 360);

public:

	/**
	 * Obtem a raíz quadrada do valor.
	 *
	 * @param Value Radicando.
	 * @return Retorna a raíz quadrada do valor.
	 * @ref http://ilab.usc.edu/wiki/index.php/Fast_Square_Root
	 */
	FORCEINLINE static float Sqrt(float Value)
	{
		IntFloatUnion Union(Value);

		Union.Int = (1 << 29) + (Union.Int >> 1) - (1 << 22);
		Union.Float = Union.Float + Value / Union.Float;

		return 0.25f * Union.Float + Value / Union.Float;
	}

	/**
	 * Obtém a raiz quadrada invertida do valor.
	 *
	 * @param Radicando.
	 *	@return Retorna a raiz quadrada invertida.
	 * @ref http://www.files.sauliaus.info/InvSqrt.pdf
	 */
	FORCEINLINE static float InvSqrt(const float Value)
	{
		IntFloatUnion Union(Value);

		Union.Int = 0x5F3759DF - (Union.Int >> 1);
		
		return Union.Float * (1.5f - (0.5f * Value * Union.Float * Union.Float));
	}

public:

	/** Retorna o valor absoluto */
	template<class T>
	FORCEINLINE static T Abs(const T Value)
	{
		return Value < 0 ? -Value : Value; 
	}

	/** Retorna o maior de dois valores */
	template<class T>
	FORCEINLINE static T Max(const T Lhs, const T Rhs)
	{
		return Lhs > Rhs ? Lhs : Rhs;
	}

	/** Retona o menor de dois valores */
	template<class T>
	FORCEINLINE static T Min(const T Lhs, const T Rhs)
	{
		return Lhs < Rhs ? Lhs : Rhs;
	}

	/** Retorna o valor multiplicado por ele mesmo */
	template<class T>
	FORCEINLINE static T Square(const T Value)
	{
		return Value * Value;
	}

	/** Retorna o valor limitado entre o valor mínimo e máximo. */
	template<class T>
	FORCEINLINE static T Clamp(const T Value, const T Min, const T Max)
	{
		return Value > Max ? Max : Value < Min ? Min : Value;
	}

	/** Retorna o valor limitado entre o valor zero e um. */
	template<class T>
	FORCEINLINE static T Clamp01(const T Value)
	{
		return Value > 1 ? 1 : Value < 0 ? 0 : Value;
	}

public:

	FORCEINLINE static float Sine(float Radians)
	{
		// TODO: Implementar minhas proprias funções trigonométricas
		return sin(Radians);
	}

	FORCEINLINE static float Cossine(const float Randians)
	{
		// TODO: Implementar minhas proprias funções trigonométricas
		return cos(Randians);
	}

	FORCEINLINE static float Tan(const float Randians)
	{
		// TODO: Implementar minhas proprias funções trigonométricas
		return tan(Randians);
	}

};