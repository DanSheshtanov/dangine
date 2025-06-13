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
        0
    };
    

    return XMVector3Normalize(direction);
}

XMMATRIX Transform::GetWorldMatrix()
{
    XMMATRIX scaleMat = XMMatrixScalingFromVector(scale);
    XMMATRIX rotationMat = XMMatrixRotationRollPitchYawFromVector(eulerRotation);
    XMMATRIX translationMat = XMMatrixTranslationFromVector(position);
    return scaleMat * rotationMat* translationMat;
}
