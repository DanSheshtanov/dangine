#pragma once

#include <DirectXMath.h>
#include "Transform.h"

using namespace DirectX;

class Camera
{
public:
	Transform transform;

	float fov = 65;
	float nearClippingPlane = 0.1f;
	float farClippingPlane = 100.0f;

	XMMATRIX GetViewMatrix();
	XMMATRIX GetProjectionMatrix(int screenWidth, int screenHeight);
};

