#pragma once

#include <DirectXMath.h>

#define MAX_POINT_LIGHTS 8

struct DirectionalLight
{
    DirectX::XMVECTOR directionFrom{ 0.2f, 0.75f, 0.3f, 1 }; // Not normalised
    DirectX::XMVECTOR colour{ 0.9f, 0.8f, 0.8f, 1 };
};

struct PointLight
{
    DirectX::XMVECTOR position;
    DirectX::XMVECTOR colour;
    float strength = 1;
    bool enabled = false;
};