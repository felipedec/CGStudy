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
