// C�digo baseado no c�digo aberto da Unreal Engine

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
