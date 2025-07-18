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
    // Got Right
    //XMVECTOR direction
    //{
    //    cos(XMVectorGetX(eulerRotation)) * cos(XMVectorGetY(eulerRotation)),// X
    //    sin(XMVectorGetX(eulerRotation)),                                   // Y
    //    cos(XMVectorGetX(eulerRotation)) * sin(XMVectorGetY(eulerRotation)),// Z
    //    1
    //};

    // Got Up
    //XMVECTOR direction
    //{
    //    cos(XMVectorGetY(eulerRotation)) * sin(XMVectorGetX(eulerRotation)),// X
    //    cos(XMVectorGetX(eulerRotation)),                                   // Y
    //    cos(XMVectorGetY(eulerRotation)) * sin(XMVectorGetX(eulerRotation)),// Z
    //    0
    //};

    //XMVECTOR direction
    //{
    //    sin(XMVectorGetY(eulerRotation)) * sin(XMVectorGetX(eulerRotation)),// X
    //    cos(XMVectorGetX(eulerRotation)),                                   // Y
    //    cos(XMVectorGetY(eulerRotation)) * sin(XMVectorGetX(eulerRotation)),// Z
    //    0
    //};

    float pitch = XMVectorGetX(eulerRotation);
    float yaw = XMVectorGetY(eulerRotation);
    XMVECTOR direction
    {
        cos(pitch) * sin(yaw),  // X
        sin(pitch),             // Y
        cos(pitch) * cos(yaw),  // Z
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
        cos(roll)* cos(yaw) + sin(roll) * sin(pitch) * sin(yaw),    // X
        sin(roll)* cos(pitch),                                      // Y
        cos(roll) * -sin(yaw) + sin(roll) * sin(pitch) * cos(yaw),  // Z
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
