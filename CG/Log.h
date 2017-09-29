/*----------------------------------------------------------------------------
			Este c�digo pertence a um projeto pessoal,
			baseado no c�digo aberto da Unreal Engine,
			com o intuito de aprendizado. Apenas as
			estrutura b�sica das classes s�o semelhantes
			e as vezes iguais, j� os corpos de m�todos
			s�o implementa��es pr�prias do desenvolvedor
			deste projeto.
			
			Saiba mais:
			https://github.com/felipedec/CGStudy
----------------------------------------------------------------------------*/

#pragma once

#include "CoreFwd.h"

namespace ELogSeverity
{
	enum Type
	{
		Warning,
		Error,
		Info
	};
}

/* -------------------------------------------- */
#define ENGINE_LOG(Severity, MessageStream)		 \
	LogImpl::OnLog<ELogSeverity>();					 \
	std::cout << MessageStream << std::endl;		 \
/* -------------------------------------------- */

namespace LogImpl
{
	template<ELogSeverity::Type Severity>
	FORCEINLINE static void OnLog() { }


	template<>
	FORCEINLINE static void OnLog<ELogSeverity::Error>()
	{
		std::getchar();
		exit(-1);
	}
}