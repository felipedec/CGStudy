// Este c�digo pertence a um projeto pessoal,
// baseado no c�digo aberto da Unreal Engine,
// com o intuito de aprendizado. Apenas as 
// estrutura b�sica das classes s�o semelhantes
// e as vezes iguais, j� os corpos de m�todos
// s�o implementa��es pr�prias do desenvolvedor
// deste projeto.
//
// Saiba mais:
// https://github.com/felipedec/CGStudy

#pragma once

#include "Vector3.h"

const FVector3 FVector3::Zero(0, 0, 0);
const FVector3 FVector3::One(1, 1, 1);
const FVector3 FVector3::Right(1, 0, 0);
const FVector3 FVector3::Left(-1, 0, 0);
const FVector3 FVector3::Up(0, 1, 0);
const FVector3 FVector3::Down(0, -1, 0);
const FVector3 FVector3::Forward(0, 0, 1);
const FVector3 FVector3::Back(0, 0, -1);
