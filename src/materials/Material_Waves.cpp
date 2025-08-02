#include "Material_Waves.h"

#include <d3d11.h>

Material_Waves::Material_Waves(std::string name, ID3D11Device* dev,
	std::string vShaderFilename, std::string pShaderFilename, Texture* texture)
	: Material(name, dev, vShaderFilename, pShaderFilename, texture)
{
	CreateCBuffer(sizeof(CBufferWaves));
}

void Material_Waves::UpdateMaterial(Entity* entity)
{
	Material::UpdateMaterial(entity);

	CBufferWaves cbData;
	cbData.waveSpeed = 1;

	UpdateCBuffer(cbData);
}
