// Código baseado no código aberto da Unreal Engine

#pragma once

#include "Core.h" 

#define UNDERLYING_TYPE(Enum) __underlying_type(Enum)

#define ENUM_CLASS_FLAGS(Enum) \
	inline Enum& operator|=(Enum& Lhs, Enum Rhs) \
   { \
      return Lhs = (Enum)((UNDERLYING_TYPE(Enum))Lhs | (UNDERLYING_TYPE(Enum))Rhs); \
   } \
	inline Enum& operator&=(Enum& Lhs, Enum Rhs) \
   { \
      return Lhs = (Enum)((UNDERLYING_TYPE(Enum))Lhs & (UNDERLYING_TYPE(Enum))Rhs); \
   } \
	inline Enum& operator^=(Enum& Lhs, Enum Rhs) \
   { \
      return Lhs = (Enum)((UNDERLYING_TYPE(Enum))Lhs ^ (UNDERLYING_TYPE(Enum))Rhs); \
   } \
	inline CONSTEXPR Enum operator|(Enum Lhs, Enum Rhs) \
   { \
      return (Enum)((UNDERLYING_TYPE(Enum))Lhs | (UNDERLYING_TYPE(Enum))Rhs); \
   } \
	inline CONSTEXPR Enum operator&(Enum Lhs, Enum Rhs) \
   { \
      return (Enum)((UNDERLYING_TYPE(Enum))Lhs & (UNDERLYING_TYPE(Enum))Rhs); \
   } \
	inline CONSTEXPR Enum operator^(Enum  Lhs, Enum Rhs) \
   { \
      return (Enum)((UNDERLYING_TYPE(Enum))Lhs ^ (UNDERLYING_TYPE(Enum))Rhs); \
   } \
	inline CONSTEXPR bool operator!(Enum E) \
   { \
      return !(UNDERLYING_TYPE(Enum))E; \
   } \
	inline CONSTEXPR Enum operator~(Enum  E) \
   { \
      return (Enum)~(UNDERLYING_TYPE(Enum))E; \
   }

template<typename Enum>
inline TEnableIfType<IsEnum<Enum>, bool> EnumHasAllFlags(Enum Flags, Enum Contains)
{
   return (((UNDERLYING_TYPE(Enum))Flags) & (UNDERLYING_TYPE(Enum))Contains) == ((UNDERLYING_TYPE(Enum))Contains);
}

template<typename Enum>
inline TEnableIfType<IsEnum<Enum>, bool> EnumHasAnyFlags(Enum Flags, Enum Contains)
{
   return (((UNDERLYING_TYPE(Enum))Flags) & (UNDERLYING_TYPE(Enum))Contains) != 0;
}