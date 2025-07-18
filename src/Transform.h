#pragma once

#include <d3d11.h>
#include <DirectXMath.h>

using namespace DirectX;

class Transform
{
public:
	
	XMVECTOR position{ 0,0,0,1 };
	XMVECTOR eulerRotation{ 0,0,0,1 };
	XMVECTOR scale{ 1,1,1,1 };

	void Translate(XMVECTOR translation);
	void Rotate(XMVECTOR rotation);

	XMVECTOR GetForward();
	XMVECTOR GetRight();
	XMVECTOR GetUp();
	XMMATRIX GetWorldMatrix();
};

