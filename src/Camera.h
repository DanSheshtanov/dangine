#pragma once

#include <DirectXMath.h>
#include "Transform.h"

using namespace DirectX;

class Camera
{
public:
	Transform transform;

	float fov = 65;
	float nearClippingPlane = 0.1;
	float farClippingPlane = 100;

	XMMATRIX GetViewMatrix();
	XMMATRIX GetProjectionMatrix(int screenWidth, int screenHeight);
};

