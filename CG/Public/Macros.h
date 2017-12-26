// Código baseado no código aberto da Unreal Engine

#pragma once

#define PREPROCESSOR_TO_STRINGW(x) TEXT(PREPROCESSOR_TO_STRING_INNER(x))
#define PREPROCESSOR_TO_STRING(x) PREPROCESSOR_TO_STRING_INNER(x)
#define PREPROCESSOR_TO_STRING_INNER(x) #x

#if defined(__clang__)
   #define PRAGMA(Token) _Pragma(Token)
#else
   #define PRAGMA(Token) __pragma(Token)
#endif // __clang__


#define PUSH_MACRO(Name) PRAGMA(push_macro(PREPROCESSOR_TO_STRING(Name)))
#define POP_MACRO(Name) PRAGMA(pop_macro(PREPROCESSOR_TO_STRING(Name)))
#define WARNING(Code) PRAGMA(warning(Code))


#if _DEBUG
	#define check(Expression) \
      if (!Expression) \
      { \
         LE_DebugLog(PREPROCESSOR_TO_STRINGW(Expression)); \
      } 
#else
	#define check(Condition)
#endif