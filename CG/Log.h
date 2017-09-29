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