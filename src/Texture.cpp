#include "Texture.h"

#include <WICTextureLoader.h>
#include <d3d11.h>

#include "Renderer.h"


Texture::Texture(Renderer& renderer, std::string path)
{
    ID3D11Device* dev = renderer.GetDevice();
    ID3D11DeviceContext* devcon = renderer.GetDeviceCon();
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
