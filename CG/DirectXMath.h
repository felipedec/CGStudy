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

#include "CoreFwd.h"

#include <DirectXMath.h>

FORCEINLINE void VectorMatrixMultiply(FMatrix* OutResult, const FMatrix* Lhs, const FMatrix* Rhs)
{
	DirectX::XMMATRIX	XMLhs = DirectX::XMLoadFloat4x4A((const DirectX::XMFLOAT4X4A*)(Lhs));
	DirectX::XMMATRIX	XMRhs = DirectX::XMLoadFloat4x4A((const DirectX::XMFLOAT4X4A*)(Rhs));
	DirectX::XMMATRIX	XMResult = DirectX::XMMatrixMultiply(XMLhs, XMRhs);
	DirectX::XMStoreFloat4x4A((DirectX::XMFLOAT4X4A*)(OutResult), XMResult);
}	

FORCEINLINE void VectorMatrixTransformFVector4(FVector4* OutResult, const FMatrix* Matrix, const FVector4* Vector)
{
	DirectX::XMVECTOR XMVector = DirectX::XMLoadFloat4A((const DirectX::XMFLOAT4A*)(Vector));
	DirectX::XMMATRIX	XMMatrix = DirectX::XMLoadFloat4x4A((const DirectX::XMFLOAT4X4A*)(Matrix));
	DirectX::XMVECTOR XMResult = DirectX::XMVector3Transform(XMVector, XMMatrix);
	DirectX::XMStoreFloat4A((DirectX::XMFLOAT4A*)(OutResult), XMResult);
}

FORCEINLINE void VectorMatrixInverse(FMatrix* OutResult, const FMatrix* Matrix)
{
	DirectX::XMMATRIX	XMMatrix = DirectX::XMLoadFloat4x4A((const DirectX::XMFLOAT4X4A*)(Matrix));
	DirectX::XMMATRIX XMResult = DirectX::XMMatrixInverse(nullptr, XMMatrix);
	DirectX::XMStoreFloat4x4A((DirectX::XMFLOAT4X4A*)(OutResult), XMResult);
}