#include "Transform.h"

void Transform::Translate(XMVECTOR translation)
{
    position = XMVectorAdd(position, translation);
}

void Transform::Rotate(XMVECTOR rotation)
{
    eulerRotation = XMVectorAddAngles(eulerRotation, rotation);
}

XMVECTOR Transform::GetForward()
{
    float pitch = XMVectorGetX(eulerRotation);
    float yaw = XMVectorGetY(eulerRotation);
    XMVECTOR direction
    {
        cosf(pitch) * sinf(yaw), // X
        sinf(pitch),             // Y
        cosf(pitch) * cosf(yaw), // Z
        0.0f
    };
    

    return XMVector3Normalize(direction);
}

XMVECTOR Transform::GetRight()
{
    float pitch = XMVectorGetX(eulerRotation);
    float yaw = XMVectorGetY(eulerRotation);
    float roll = XMVectorGetZ(eulerRotation);
    
    XMVECTOR direction
    {
        cosf(roll) * cosf(yaw) + sinf(roll) * sinf(pitch) * sinf(yaw),  // X
        sinf(roll) * cosf(pitch),                                       // Y
        cosf(roll) * -sinf(yaw) + sinf(roll) * sinf(pitch) * cosf(yaw), // Z
        0.0f
    };

    // This works without camera roll
    //XMVECTOR direction
    //{
    //    sin(yaw + XM_PIDIV2), // X
    //    0.0f,                 // Y
    //    cos(yaw + XM_PIDIV2), // Z
    //    0.0f
    //};

    return XMVector3Normalize(direction);
}

XMVECTOR Transform::GetUp()
{
    XMVECTOR cross = XMVector3Cross(GetForward(), GetRight());

    return XMVector3Normalize(cross);
}

XMMATRIX Transform::GetWorldMatrix()
{
    XMMATRIX scaleMat = XMMatrixScalingFromVector(scale);
    XMMATRIX rotationMat = XMMatrixRotationRollPitchYawFromVector(eulerRotation);
    XMMATRIX translationMat = XMMatrixTranslationFromVector(position);
    return scaleMat * rotationMat* translationMat;
}
