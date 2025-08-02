#pragma once
#include "Material.h"

#include <DirectXMath.h>

class Material_Waves : public Material
{
public:
    struct CBufferWaves : CBufferBase
    {
        float waveSpeed = 1;
        DirectX::XMFLOAT3 padding;
    };

    Material_Waves(std::string name, ID3D11Device* dev,
        std::string vShaderFilename, std::string pShaderFilename,
        Texture* texture);

    virtual void UpdateMaterial(Entity* entity) override;
};

