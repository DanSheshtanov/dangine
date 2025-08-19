#pragma once

#include <DirectXMath.h>

using namespace DirectX;

class Transform
{
public:
	
	DirectX::XMVECTOR position{ 0,0,0,1 };
	DirectX::XMVECTOR eulerRotation{ 0,0,0,1 };
	DirectX::XMVECTOR scale{ 1,1,1,1 };

	void Translate(DirectX::XMVECTOR translation);
	void Rotate(DirectX::XMVECTOR rotation);

	DirectX::XMVECTOR GetForward();
	DirectX::XMVECTOR GetRight();
	DirectX::XMVECTOR GetUp();
	DirectX::XMMATRIX GetWorldMatrix();
};

