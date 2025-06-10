#pragma once
#include <string>

struct ID3D11VertexShader;
struct ID3D11PixelShader;
struct ID3D11InputLayout;
struct ID3D11Device;

class Material
{
public:
	Material(std::string name, ID3D11Device* dev, std::string vShaderFilename, std::string pShaderFilename);
	void SetActive(ID3D11DeviceContext* devcon);
private:
	std::string name;

	ID3D11Device* dev			= nullptr;
	ID3D11VertexShader* vShader	= nullptr;
	ID3D11InputLayout* vLayout	= nullptr;
	ID3D11PixelShader* pShader	= nullptr;

};

