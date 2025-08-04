#pragma once
#include "Material.h"

#include <DirectXMath.h>

class Material_Lit : public Material
{
public:
    struct CBufferLighting : CBufferBase
    {
        DirectX::XMVECTOR ambientLight{ 1,1,1,1 };
        DirectX::XMVECTOR directionalLightDir{ 0,1,0,1 };
        DirectX::XMVECTOR directionalLightCol{ 1,1,1,1 };
    };

	Material_Lit(std::string name, ID3D11Device* dev,
		std::string vShaderFilename, std::string pShaderFilename,
		Texture* texture);

    virtual void UpdateMaterial(Entity * entity) override;
};

