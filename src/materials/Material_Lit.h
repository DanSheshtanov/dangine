#pragma once
#include "Material.h"

#include <DirectXMath.h>

#define MAX_POINT_LIGHTS 8

class Material_Lit : public Material
{
public:
    struct DirectionalLight
    {
        DirectX::XMVECTOR transposedDirection;
        DirectX::XMVECTOR colour;
    };
    struct PointLight
    {
        DirectX::XMVECTOR position; // 16 bytes
        DirectX::XMVECTOR colour; // 16 bytes
        float strength = 1; // 4 bytes
        unsigned int enabled = 0; // 4 bytes
        DirectX::XMFLOAT2 padding; // 8 bytes
    };
    struct CBufferLighting : CBufferBase
    {
        DirectX::XMVECTOR ambientLight{ 1,1,1,1 };
        DirectionalLight directionalLight;
        PointLight pointLights[MAX_POINT_LIGHTS];
    };

	Material_Lit(std::string name, Renderer& renderer,
		std::string vShaderFilename, std::string pShaderFilename,
		Texture* texture);

    virtual void UpdateMaterial(Entity * entity) override;
};

