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

using namespace DirectX;

namespace Engine_Private
{
	FORCEINLINE void VectorMatrixMultiply(FMatrix* OutResult, const FMatrix& Lhs, const FMatrix& Rhs)
	{
		XMMATRIX	XMLhs = XMLoadFloat4x4A((const XMFLOAT4X4A*)&Lhs);
		XMMATRIX	XMRhs = XMLoadFloat4x4A((const XMFLOAT4X4A*)&Rhs);
		XMMATRIX	XMResult = XMMatrixMultiply(XMLhs, XMRhs);

		XMStoreFloat4x4A((XMFLOAT4X4A*)OutResult, XMResult);
	}	

	FORCEINLINE void VectorMatrixTransformFVector4(FVector4* OutResult, const FMatrix& Matrix, const FVector4& Vector)
	{
		XMVECTOR XMVector = XMLoadFloat4A((const XMFLOAT4A*)&Vector);
		XMMATRIX	XMMatrix = XMLoadFloat4x4A((const XMFLOAT4X4A*)&Matrix);
		XMVECTOR XMResult = XMVector3Transform(XMVector, XMMatrix);

		XMStoreFloat4A((XMFLOAT4A*)OutResult, XMResult);
	}

	FORCEINLINE void VectorMatrixInverse(FMatrix* OutResult, const FMatrix& Matrix)
	{
		XMMATRIX	XMMatrix = XMLoadFloat4x4A((const XMFLOAT4X4A*)&Matrix);
		XMMATRIX XMResult = XMMatrixInverse(nullptr, XMMatrix);

		XMStoreFloat4x4A((XMFLOAT4X4A*)OutResult, XMResult);
	}

	FORCEINLINE void QuaternionRotationAxis(FQuaternion* OutResult, const FVector& Axis, const float AngleRad)
	{
		XMVECTOR XMVector = XMLoadFloat3((const XMFLOAT3*)&Axis);
		XMVECTOR XMResult = XMQuaternionRotationAxis(XMVector, AngleRad);

		XMStoreFloat4A((XMFLOAT4A*)OutResult, XMResult);
	}

	FORCEINLINE void RotationMatrix2Quaternion(FQuaternion* OutResult, const FMatrix& RotMat)
	{
		XMMATRIX	XMMatrix = XMLoadFloat4x4A((const XMFLOAT4X4A*)&RotMat);
		XMVECTOR XMResult = XMQuaternionRotationMatrix(XMMatrix);

		XMStoreFloat4A((XMFLOAT4A*)OutResult, XMResult);
	}

	FORCEINLINE float QuaternionDot(const FQuaternion& Lhs, const FQuaternion& Rhs)
	{
		XMVECTOR XMLhs = XMLoadFloat4A((const XMFLOAT4A*)&Lhs);
		XMVECTOR XMRhs = XMLoadFloat4A((const XMFLOAT4A*)&Rhs);

		return XMQuaternionDot(XMLhs, XMRhs).m128_f32[0];
	}

	FORCEINLINE void QuaternionTransformFVector(FVector* OutResult, const FQuaternion& Quat, const FVector& Vector)
	{
		XMVECTOR XMVector = XMLoadFloat3((const XMFLOAT3*)&Vector);
		XMVECTOR XMQuat = XMLoadFloat4A((const XMFLOAT4A*)&Quat);
		XMVECTOR XMResult = XMVector3Rotate(XMVector, XMQuat);

		XMStoreFloat3((XMFLOAT3*)OutResult, XMResult);
	}

	FORCEINLINE void QuaternionMultiply(FQuaternion* OutResult, const FQuaternion& Lhs, const FQuaternion& Rhs)
	{
		XMVECTOR XMLhs = XMLoadFloat4A((const XMFLOAT4A*)&Lhs);
		XMVECTOR XMRhs = XMLoadFloat4A((const XMFLOAT4A*)&Rhs);
		XMVECTOR XMResult = XMQuaternionMultiply(XMLhs, XMRhs);

		XMStoreFloat4A((XMFLOAT4A*)OutResult, XMResult);
	}

	FORCEINLINE void QuaternionRotationEulerVector(FQuaternion* OutResult, const FVector& Angles)
	{
		XMVECTOR XMAngles = XMLoadFloat3((const XMFLOAT3*)&Angles);;
		XMVECTOR XMResult = XMQuaternionRotationRollPitchYawFromVector(XMAngles);

		XMStoreFloat4A((XMFLOAT4A*)OutResult, XMResult);
	}

	FORCEINLINE void Quaternion2RotationMatrix(FMatrix* OutResult, const FQuaternion& Quaternion)
	{
		XMVECTOR XMQuaternion = XMLoadFloat4A((const XMFLOAT4A*)&Quaternion);
		XMMATRIX XMResult = XMMatrixRotationQuaternion(XMQuaternion);

		XMStoreFloat4x4A((XMFLOAT4X4A*)OutResult, XMResult);
	}
}