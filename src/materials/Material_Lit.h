#pragma once
#include "Material.h"
#include "Lighting.h"


class Material_Lit : public Material
{
public:
    float reflectiveness = 0.1f;

	Material_Lit(std::string name, Renderer& renderer,
		std::string vShaderFilename, std::string pShaderFilename,
		Texture* texture);

    virtual void UpdateMaterial(Entity * entity) override;

    void SetReflectionTexture(Texture* reflectionTexture) { skyboxTexture = reflectionTexture; }

protected:
    Texture* skyboxTexture = nullptr;
    ID3D11Buffer* cbufferPixelShader = nullptr;

    struct DirectionalLightCB
    {
        DirectX::XMVECTOR transposedDirection;
        DirectX::XMVECTOR colour;
    };
    struct PointLightCB
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
        DirectionalLightCB directionalLight;
        PointLightCB pointLights[MAX_POINT_LIGHTS];
    };

    struct CBufferPS : CBufferBase
    {
        float reflectiveness;
        DirectX::XMFLOAT3 padding;
    };
};