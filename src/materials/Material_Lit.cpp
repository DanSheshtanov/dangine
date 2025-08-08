#include "Material_Lit.h"

#include <d3d11.h>

#include "Debug.h"
#include "Entity.h"

Material_Lit::PointLight pointLights[MAX_POINT_LIGHTS];

Material_Lit::Material_Lit(std::string name, Renderer& renderer,
	std::string vShaderFilename, std::string pShaderFilename, Texture* texture)
	: Material(name, renderer, vShaderFilename, pShaderFilename, texture)
{
	CreateCBuffer(sizeof(CBufferLighting));

	pointLights[0].enabled = 1;
	pointLights[0].colour = { 0,1,1,1 };
	pointLights[0].position = { 0, 1, -2 };
	pointLights[0].strength = 2;
;}

void Material_Lit::UpdateMaterial(Entity* entity)
{
	using namespace DirectX;
	Material::UpdateMaterial(entity);

	static float fakeTime = 0;
	fakeTime += 0.0001f;
	pointLights[0].position = XMVectorSetX(pointLights[0].position, sin(fakeTime) * 5);
	LOG(std::to_string(XMVectorGetX(pointLights[0].position)));

	CBufferLighting cbData;
	//cbData.ambientLight = { 0.3f,0.1f,0.1f,1.f };
	cbData.ambientLight = { 0,0,0,1 };
	//cbData.directionalLight.colour = XMVECTOR{ 1,1,0.9f,1 };
	cbData.directionalLight.colour = XMVECTOR{ 0,0,0,1 };
	XMMATRIX transpose = XMMatrixTranspose(entity->transform.GetWorldMatrix()); // Transpose rotations
	cbData.directionalLight.transposedDirection = XMVector3Transform(XMVECTOR{ 0, 1, 0 }, transpose);

	// Point lighting
	for (size_t i = 0; i < MAX_POINT_LIGHTS; ++i)
	{
		cbData.pointLights[i].enabled = pointLights[i].enabled;

		if (!pointLights[i].enabled)
			continue; // Skip disabled lights

		XMMATRIX inverse = XMMatrixInverse(nullptr, entity->transform.GetWorldMatrix());

		cbData.pointLights[i].position = XMVector3Transform(pointLights[i].position, inverse);
		cbData.pointLights[i].colour = pointLights[i].colour;
		cbData.pointLights[i].strength = pointLights[i].strength;
	}
	UpdateCBuffer(cbData);
}

