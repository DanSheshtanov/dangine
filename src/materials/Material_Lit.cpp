#include "Material_Lit.h"

#include <d3d11.h>

#include "Entity.h"

Material_Lit::Material_Lit(std::string name, ID3D11Device* dev,
	std::string vShaderFilename, std::string pShaderFilename, Texture* texture)
	: Material(name, dev, vShaderFilename, pShaderFilename, texture)
{
	CreateCBuffer(sizeof(CBufferLighting));
}

void Material_Lit::UpdateMaterial(Entity* entity)
{
	using namespace DirectX;
	Material::UpdateMaterial(entity);

	CBufferLighting cbData;
	cbData.ambientLight = { 0.3f,0.1f,0.1f,1.f };
	cbData.directionalLightCol = XMVECTOR{ 1,1,0.9f,1 };
	XMMATRIX transpose = XMMatrixTranspose(entity->transform.GetWorldMatrix()); // Transpose rotations
	cbData.directionalLightDir = XMVector3Transform(XMVECTOR{ 0, 1, 0 }, transpose);
	UpdateCBuffer(cbData);
}

