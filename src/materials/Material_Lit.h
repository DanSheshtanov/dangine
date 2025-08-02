#pragma once
#include "Material.h"

#include <DirectXMath.h>

class Material_Lit : public Material
{
public:
    struct CBufferLighting : CBufferBase
    {
        DirectX::XMFLOAT4 ambientLight{ 1,1,1,1 };
    };

	Material_Lit(std::string name, ID3D11Device* dev,
		std::string vShaderFilename, std::string pShaderFilename,
		Texture* texture);

    virtual void UpdateMaterial(Entity * entity) override;
};

