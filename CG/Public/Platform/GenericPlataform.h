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

/*----------------------------------------------------------------------------
			Traits usado para automaticamente selecionar o tipo correto 
			dependendo do tamanho do barramento da plataforma.

			Nota:
			Já Existe um trait específico para isso em Templates/TypeTraits.h,
			porém por motivos da ordem da inclusão dos arquivos é necessário
			implementar aqui novamente.
----------------------------------------------------------------------------*/

namespace Engine_Private
{
	template<bool, typename T32Bits, typename T64Bits>
	struct TSelectPlatformTypeHelper
	{
		using Type = T32Bits;
	};

	template<typename T32Bits, typename T64Bits>
	struct TSelectPlatformTypeHelper<false, T32Bits, T64Bits>
	{
		using Type = T64Bits;
	};

	template<typename T32Bits, typename T64Bits> struct TSelectPlatformType 
		: TSelectPlatformTypeHelper<sizeof(void*) == 4, T32Bits, T64Bits> { };
}

/*----------------------------------------------------------------------------
			Praticamente a mesma estrutura encontrada em
			Runtime/Core/Public/GenericPlatform/GenericPlatform.h 
----------------------------------------------------------------------------*/

struct FGenericPlatformTypes
{
public:

	// Tipos sem sinal.
	typedef unsigned char uint8; 
	typedef unsigned short int	uint16;
	typedef unsigned int uint32;
	typedef unsigned long long	uint64;

public:

	// Tipos com sinal.
	typedef signed char int8;
	typedef signed short int int16;
	typedef signed int int32;
	typedef signed long long int64;

public:

	// Tipos de caractérios.
	typedef char ANSICHAR;
	typedef wchar_t WIDECHAR;
	typedef uint8 CHAR8;
	typedef uint16 CHAR16;
	typedef uint32 CHAR32;
	typedef WIDECHAR TCHAR;

public:
	
	// Tipos inteiros de mesmo tamanho de um pointeiro.
	typedef Engine_Private::TSelectPlatformType<uint32, uint64>::Type UPTRINT;
	typedef Engine_Private::TSelectPlatformType<int32, int64>::Type PTRINT;

public:

	typedef UPTRINT SIZE_T;
	typedef PTRINT SSIZE_T;
	typedef int32 TYPE_OF_NULL;
	typedef decltype(nullptr) TYPE_OF_NULLPTR;
};

typedef FGenericPlatformTypes FPlataformTypes;

typedef FPlataformTypes::uint8 uint8;
typedef FPlataformTypes::uint16 uint16;
typedef FPlataformTypes::uint32 uint32;
typedef FPlataformTypes::uint64 uint64;

typedef FPlataformTypes::int8 int8;
typedef FPlataformTypes::int16 int16;
typedef FPlataformTypes::int32 int32;
typedef FPlataformTypes::int64 int64;

typedef FPlataformTypes::ANSICHAR ANSICHAR;
typedef FPlataformTypes::WIDECHAR WIDECHAR;
typedef FPlataformTypes::CHAR8 CHAR8;
typedef FPlataformTypes::CHAR16 CHAR16;
typedef FPlataformTypes::CHAR32 CHAR32;
typedef FPlataformTypes::TCHAR TCHAR;

typedef FPlataformTypes::UPTRINT UPTRINT;
typedef FPlataformTypes::PTRINT PTRINT;

typedef FPlataformTypes::SIZE_T SIZE_T;
typedef FPlataformTypes::SSIZE_T SSIZE_T;
typedef FPlataformTypes::TYPE_OF_NULL TYPE_OF_NULL;
typedef FPlataformTypes::TYPE_OF_NULLPTR TYPE_OF_NULLPTR;