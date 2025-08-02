#include "Material_Lit.h"

#include <d3d11.h>

#include "Debug.h"

Material_Lit::Material_Lit(std::string name, ID3D11Device* dev,
	std::string vShaderFilename, std::string pShaderFilename, Texture* texture)
	: Material(name, dev, vShaderFilename, pShaderFilename, texture)
{
	CreateCBuffer(sizeof(CBufferLighting));
}

void Material_Lit::UpdateMaterial(Entity* entity)
{
	Material::UpdateMaterial(entity);

	CBufferLighting cbData;
	cbData.ambientLight = { 1,0.5f,0.5f,0.2f };
	UpdateCBuffer(cbData);
}

