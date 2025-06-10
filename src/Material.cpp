#include <d3d11.h>
#include "ShaderLoading.h"
#include "Debug.h"
#include "Material.h"

Material::Material(std::string name, ID3D11Device* dev,
	std::string vShaderFilename, std::string pShaderFilename)
	:name(name), dev(dev)
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
