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

#include "Core.h"
#include "CoreFwd.h"


class CORE_API LObject
{
	
};

class CORE_API LMember : public LObject
{
public:
	
	

};

class CORE_API LProperty : public LMember
{
public:



};



class CORE_API LFunction : public LMember
{
public:



};


class CORE_API LClass : public LObject
{
public:

	FORCEINLINE virtual LObject CreateInstance()
	{
		return LObject();
	}

public:
};
