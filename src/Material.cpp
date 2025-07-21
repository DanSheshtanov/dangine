#include "Material.h"

#include <d3d11.h>

#include "Texture.h"
#include "ShaderLoading.h"
#include "Debug.h"

Material::Material(std::string name, ID3D11Device* dev,
	std::string vShaderFilename, std::string pShaderFilename,
	Texture* texture = nullptr)
	:name(name), dev(dev), texture(texture)
{
	HRESULT hr;
	hr = ShaderLoading::LoadVertexShader(vShaderFilename, dev, &vShader, &vLayout);
	if (FAILED(hr))
	{
		LOG("Material " + name + " failed to load, aborting.");
		return;
	}

	hr = ShaderLoading::LoadPixelShader(pShaderFilename, dev, &pShader);
	if (FAILED(hr))
	{
		LOG("Material " + name + " failed to load, aborting.");
		return;
	}
}

void Material::Bind(ID3D11DeviceContext* devcon)
{
	//dev->GetImmediateContext

	devcon->VSSetShader(vShader, 0, 0);
	devcon->PSSetShader(pShader, 0, 0);
	devcon->IASetInputLayout(vLayout);

	// TODO funny bug where non-textured mats will render with previous textures
	if (texture != nullptr)
	{
		ID3D11SamplerState* s = texture->GetSampler();
		devcon->PSSetSamplers(0, 1, &s);
		ID3D11ShaderResourceView* t = texture->GetTexture();
		devcon->PSSetShaderResources(0, 1, &t);
	}
}
