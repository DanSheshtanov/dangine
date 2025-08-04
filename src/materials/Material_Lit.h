#pragma once
#include "Material.h"

#include <DirectXMath.h>

class Material_Lit : public Material
{
public:
    struct DirectionalLight
    {
        DirectX::XMVECTOR transposedDirection;
        DirectX::XMVECTOR colour;
    };
    struct CBufferLighting : CBufferBase
    {
        DirectX::XMVECTOR ambientLight{ 1,1,1,1 };
        DirectionalLight directionalLight;
    };

	Material_Lit(std::string name, ID3D11Device* dev,
		std::string vShaderFilename, std::string pShaderFilename,
		Texture* texture);

    virtual void UpdateMaterial(Entity * entity) override;
};

