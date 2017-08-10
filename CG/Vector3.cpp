// Este código pertence a um projeto pessoal,
// baseado no código aberto da Unreal Engine,
// com o intuito de aprendizado. Apenas as 
// estrutura básica das classes são semelhantes
// e as vezes iguais, já os corpos de métodos
// são implementações próprias do desenvolvedor
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
