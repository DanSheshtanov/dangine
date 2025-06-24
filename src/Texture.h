#pragma once
#include <string>

struct ID3D11Device;
struct ID3D11DeviceContext;
struct ID3D11ShaderResourceView;
struct ID3D11SamplerState;

class Texture
{
public:
	Texture(ID3D11Device* dev, ID3D11DeviceContext* devcon, std::string path);
	ID3D11ShaderResourceView* GetTexture() { return texture; }
	ID3D11SamplerState* GetSampler() { return sampler; }

private:
	ID3D11ShaderResourceView* texture = nullptr; // Texture
	ID3D11SamplerState* sampler = nullptr; // Sampler
};

