#include "Material_Lit.h"

#include <d3d11.h>

#include "Debug.h"
#include "Entity.h"
#include "Renderer.h"
#include "Texture.h"

Material_Lit::Material_Lit(std::string name, Renderer& renderer,
	std::string vShaderFilename, std::string pShaderFilename, Texture* texture)
	: Material(name, renderer, vShaderFilename, pShaderFilename, texture)
{
	CreateCBuffer(sizeof(CBufferLighting));
	CreateCBuffer(sizeof(CBufferPS), cbufferPixelShader);
;}

void Material_Lit::UpdateMaterial(Entity* entity)
{
	using namespace DirectX;
	Material::UpdateMaterial(entity);

	ID3D11DeviceContext* devcon;
	dev->GetImmediateContext(&devcon);

	CBufferLighting cbData;
	// Ambient light
	cbData.ambientLight = renderer.GetAmbientLight();
	// Directional light
	DirectionalLight& dirLight = renderer.GetDirectionalLight();
	cbData.directionalLight.colour = dirLight.colour;
	XMMATRIX transpose = XMMatrixTranspose(entity->transform.GetWorldMatrix()); // Transpose rotations
	cbData.directionalLight.transposedDirection =
		XMVector3Transform(XMVector3Normalize(dirLight.directionFrom), transpose);

	// Point lights
	PointLight* pointLights = renderer.GetPointLights();
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

	// Skybox reflection
	if (skyboxTexture != nullptr)
	{
		ID3D11ShaderResourceView* t = skyboxTexture->GetTexture();
		devcon->PSSetShaderResources(1, 1, &t);
	}

	UpdateCBuffer(cbData);

	// Pixel shdader
	CBufferPS cbpsData;
	cbpsData.reflectiveness = reflectiveness;
	UpdateCBuffer(cbpsData, cbufferPixelShader);
	devcon->PSSetConstantBuffers(0, 1, &cbufferPixelShader); // Stinky here
}

