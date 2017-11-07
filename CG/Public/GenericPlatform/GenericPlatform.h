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

/*----------------------------------------------------------------------------
			Traits usado para automaticamente selecionar o tipo correto 
			dependendo do tamanho do barramento da plataforma.

			Nota:
			J� Existe um trait espec�fico para isso em Templates/TypeTraits.h,
			por�m por motivos da ordem da inclus�o dos arquivos � necess�rio
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

	// Tipos de caract�rios.
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

