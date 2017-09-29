/*----------------------------------------------------------------------------
			Este código pertence a um projeto pessoal,
			baseado no código aberto da Unreal Engine,
			com o intuito de aprendizado. Apenas as
			estrutura básica das classes são semelhantes
			e as vezes iguais, já os corpos de métodos
			são implementações próprias do desenvolvedor
			deste projeto.
			
			Saiba mais:
			https://github.com/felipedec/CGStudy
----------------------------------------------------------------------------*/

#pragma once

#define FORCEINLINE __forceinline
#define CONSTEXPR	constexpr

#define TEXT(Txt) (L##Txt)

#define PREPROCESSOR_TO_STRING(x) PREPROCESSOR_TO_STRING_INNER(x)
#define PREPROCESSOR_TO_STRING_INNER(x) #x

#if defined(__GNUC__)
	#define GCC_ALIGN(n) __attribute__((aligned(n)))
	#define MS_ALIGN(n)
#else
	#define GCC_ALIGN(n)
	#define MS_ALIGN(n) __declspec(align(n)) 
#endif // __GNUC__

#if defined(__clang__)
	#define PUSH_MACRO(Name) _Pragma(PREPROCESSOR_TO_STRING(push_macro(PREPROCESSOR_TO_STRING(Name))))
	#define POP_MACRO(Name) _Pragma(PREPROCESSOR_TO_STRING(pop_macro(PREPROCESSOR_TO_STRING(Name))))
	#define WARNING(Code) _Pragma(warning(Code))
#else
	#define PUSH_MACRO(Name) __pragma(push_macro(PREPROCESSOR_TO_STRING(Name)))
	#define POP_MACRO(Name) __pragma(pop_macro(PREPROCESSOR_TO_STRING(Name)))
	#define WARNING(Code) __pragma(warning(Code))
#endif // __clang__
