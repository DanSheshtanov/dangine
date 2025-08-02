#pragma once
#include "Material.h"

#include <DirectXMath.h>

class Material_Waves :
    public Material
{
public:
    struct CBufferWaves
    {
        float waveSpeed = 1;
        DirectX::XMFLOAT3 padding;
    };

    Material_Waves(std::string name, ID3D11Device* dev,
        std::string vShaderFilename, std::string pShaderFilename,
        Texture* texture);

    virtual void Bind() override;
    virtual void UpdateMaterial(Entity* entity) override;


private:
    ID3D11Buffer* constantBuffer;
};

