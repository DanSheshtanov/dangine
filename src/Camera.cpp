#include "Camera.h"

#include <DirectXMath.h>

XMMATRIX Camera::GetViewMatrix()
{
	return XMMatrixLookToLH(
		transform.position,
		transform.GetForward(),
		transform.GetUp());
		//XMVECTOR{ 0,1,0,0 });
}

XMMATRIX Camera::GetProjectionMatrix(int screenWidth, int screenHeight)
{
	return XMMatrixPerspectiveFovLH(
		XMConvertToRadians(fov),
		screenWidth / (float)screenHeight,
		nearClippingPlane,
		farClippingPlane);
}
