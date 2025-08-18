#pragma once
#include <string>

//struct ID3D11Device;
//struct ID3D11DeviceContext;
class Renderer;
struct ID3D11ShaderResourceView;
struct ID3D11SamplerState;

class Texture
{
public:
	enum class TextureType
	{
		Texture2D,
		Cubemap
	};

	Texture(Renderer& renderer, std::string path, TextureType type = TextureType::Texture2D);
	ID3D11ShaderResourceView* GetTexture() { return texture; }
	ID3D11SamplerState* GetSampler() { return sampler; }

private:
	ID3D11ShaderResourceView* texture = nullptr; // Texture
	ID3D11SamplerState* sampler = nullptr; // Sampler
};

