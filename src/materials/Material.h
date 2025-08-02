#pragma once
#include <string>

struct ID3D11VertexShader;
struct ID3D11PixelShader;
struct ID3D11InputLayout;
struct ID3D11Device;
struct ID3D11DeviceContext;
struct ID3D11Buffer; // Not used here but useful for child materials

class Texture;
class Entity;

class Material
{
public:
	Material(std::string name, ID3D11Device* dev,
		std::string vShaderFilename, std::string pShaderFilename,
		Texture* texture);

	virtual void Bind();

	virtual void UpdateMaterial(Entity* entity) {}

protected:
	std::string name;

	ID3D11Device* dev			= nullptr;
	ID3D11VertexShader* vShader	= nullptr;
	ID3D11InputLayout* vLayout	= nullptr;
	ID3D11PixelShader* pShader	= nullptr;

	Texture* texture			= nullptr;
};

