#include "Camera.h"

XMMATRIX Camera::GetViewMatrix()
{
	return XMMatrixLookToLH(
		transform.position,
		transform.GetForward(),
		XMVECTOR{ 0,1,0,0 });
}

XMMATRIX Camera::GetProjectionMatrix(int screenWidth, int screenHeight)
{
	return XMMatrixPerspectiveFovLH(
		fov,
		screenWidth / (float)screenHeight,
		nearClippingPlane,
		farClippingPlane);
}
