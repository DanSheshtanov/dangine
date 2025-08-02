#include "Material_Waves.h"

#include <d3d11.h>

#include "Debug.h"

Material_Waves::Material_Waves(std::string name, ID3D11Device* dev,
	std::string vShaderFilename, std::string pShaderFilename, Texture* texture)
	: Material(name, dev, vShaderFilename, pShaderFilename, texture)
{
	D3D11_BUFFER_DESC cbd{ 0 };
	cbd.Usage = D3D11_USAGE_DEFAULT;
	cbd.ByteWidth = sizeof(CBufferWaves);
	cbd.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
	if (FAILED(dev->CreateBuffer(&cbd, NULL, &constantBuffer)))
	{
		LOG("Oops, failed to create CBuffer.");
	}
}

void Material_Waves::Bind()
{
	Material::Bind();

	ID3D11DeviceContext* devcon;
	dev->GetImmediateContext(&devcon);
	devcon->VSSetConstantBuffers(0, 1, &constantBuffer);
}

void Material_Waves::UpdateMaterial(Entity* entity)
{
	Material::UpdateMaterial(entity);

	CBufferWaves cbData;
	cbData.waveSpeed = 1;
	
	ID3D11DeviceContext* devcon;
	dev->GetImmediateContext(&devcon);

	devcon->UpdateSubresource(constantBuffer, 0, 0, &cbData, 0, 0);
}
