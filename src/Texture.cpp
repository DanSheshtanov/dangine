//#include "WICTextureLoader.h"
#include <d3d11.h>
#include <WICTextureLoader.h>

#include "Texture.h"

Texture::Texture(ID3D11Device* dev, ID3D11DeviceContext* devcon, std::string path)
{
    DirectX::CreateWICTextureFromFile(dev, devcon, std::wstring(path.begin(), path.end()).c_str(), NULL, &texture);
    
    D3D11_SAMPLER_DESC samplerDesc;
    ZeroMemory(&samplerDesc, sizeof(D3D11_SAMPLER_DESC));
    //samplerDesc.Filter = D3D11_FILTER_MIN_MAG_MIP_LINEAR;
    samplerDesc.Filter = D3D11_FILTER_MIN_MAG_MIP_POINT;
    samplerDesc.AddressU = D3D11_TEXTURE_ADDRESS_WRAP;
    samplerDesc.AddressV = D3D11_TEXTURE_ADDRESS_WRAP;
    samplerDesc.AddressW = D3D11_TEXTURE_ADDRESS_WRAP;
    samplerDesc.MaxLOD = D3D11_FLOAT32_MAX;
    dev->CreateSamplerState(&samplerDesc, &sampler);
}
