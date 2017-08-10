// Este c�digo pertence a um projeto pessoal,
// baseado no c�digo aberto da Unreal Engine,
// com o intuito de aprendizado. Apenas as 
// estrutura b�sica das classes s�o semelhantes
// e as vezes iguais, j� os corpos de m�todos
// s�o implementa��es pr�prias do desenvolvedor
// deste projeto.
//
// Saiba mais:
// https://github.com/felipedec/CGStudy

#pragma once

#include "Core.h"

class FMath
{
public:

	/**
	*
	* Obtem a ra�z quadrada do valor com alta precis�o e baixa performance.
	*
	* @param Value Valor ao qual deve ser realizado a opera��o.
	* @return Retorna a ra�z quadrada do valor.
	* @ref http://ilab.usc.edu/wiki/index.php/Fast_Square_Root
	*/
	FORCEINLINE static float Sqrt(const float Value)
	{
		union
		{
			int I;
			float X;
		} Union;

		Union.X = Value;
		Union.I = (1 << 29) + (Union.I >> 1) - (1 << 22);

		Union.X = Union.X + Value / Union.X;
		Union.X = 0.25f * Union.X + Value / Union.X;

		return Union.X;
	}

	/** Retorna o valor absoluto */
	FORCEINLINE static float Abs(const float Value)
	{
		return Value < 0 ? -Value : Value; 
	}

	/** Retorna o maior de dois valores */
	template<class T>
	FORCEINLINE static T Max(const T A, const T B)
	{
		return A > B ? A : B;
	}

	/** Retona o menor de dois valores */
	template<class T>
	FORCEINLINE static T Min(const T A, const T B)
	{
		return A < B ? A : B;
	}

	/** Retorna o valor multiplicado por ele mesmo */
	template<class T>
	FORCEINLINE static T Square(const T Value)
	{
		return Value * Value;
	}

	/** Retorna o valor limitado entre o valor m�nimo e m�ximo. */
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
};