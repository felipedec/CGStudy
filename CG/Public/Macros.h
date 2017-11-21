/*----------------------------------------------------------------------------
			Este c�digo pertence a um projeto pessoal,
			baseado no c�digo aberto da Unreal Engine,
			com o intuito de aprendizado. Apenas as
			estrutura b�sica das classes s�o semelhantes
			e as vezes iguais, j� os corpos de m�todos
			s�o implementa��es pr�prias do desenvolvedor
			deste projeto.
			
			Saiba mais:
			https://github.com/felipedec/LeafEngine
----------------------------------------------------------------------------*/

#pragma once

#define PREPROCESSOR_TO_STRING(x) PREPROCESSOR_TO_STRING_INNER(x)
#define PREPROCESSOR_TO_STRING_INNER(x) #x

#if defined(__clang__)
	#define PUSH_MACRO(Name) _Pragma(PREPROCESSOR_TO_STRING(Name)))
	#define POP_MACRO(Name) _Pragma(PREPROCESSOR_TO_STRING(Name)))
	#define WARNING(Code) _Pragma(warning(Code))
#else
	#define PUSH_MACRO(Name) __pragma(push_macro(PREPROCESSOR_TO_STRING(Name)))
	#define POP_MACRO(Name) __pragma(pop_macro(PREPROCESSOR_TO_STRING(Name)))
	#define WARNING(Code) __pragma(warning(Code))
#endif // __clang__

#if _DEBUG
	#define check(Condition) if (Condition) LE_DebugLogError("Error!");
#else
	#define check(Condition)
#endif