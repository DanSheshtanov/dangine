#include "Material.h"

#include <d3d11.h>

#include "Renderer.h"
#include "Texture.h"
#include "ShaderLoading.h"
#include "Debug.h"

Material::Material(std::string name, Renderer& renderer,
	std::string vShaderFilename, std::string pShaderFilename,
	Texture* texture = nullptr)
	:name(name), renderer(renderer), dev(renderer.GetDevice()), texture(texture)
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

void Material::Bind()
{
	ID3D11DeviceContext* devcon;
	dev->GetImmediateContext(&devcon);

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

	if (cbuffer != nullptr)
	{
		devcon->VSSetConstantBuffers(0, 1, &cbuffer);
	}
}

void Material::CreateCBuffer(unsigned int byteWidth)
{
	D3D11_BUFFER_DESC cbd{ 0 };
	cbd.Usage = D3D11_USAGE_DEFAULT;
	cbd.ByteWidth = byteWidth;
	cbd.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
	if (FAILED(dev->CreateBuffer(&cbd, NULL, &cbuffer)))
	{
		LOG("Oops, failed to create CBuffer for material " + name);
	}
}

void Material::UpdateCBuffer(CBufferBase& cbData)
{
	ID3D11DeviceContext* devcon;
	dev->GetImmediateContext(&devcon);

	devcon->UpdateSubresource(cbuffer, 0, 0, &cbData, 0, 0);
}
