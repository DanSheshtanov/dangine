#pragma once

#include <string>

struct ID3D11VertexShader;
struct ID3D11PixelShader;
struct ID3D11InputLayout;
struct ID3D11Device;

namespace ShaderLoading
{
	int LoadVertexShader(std::string filename, ID3D11Device* dev,
		ID3D11VertexShader** outVS, ID3D11InputLayout** outIL);
	int LoadPixelShader(std::string filename, ID3D11Device* dev, ID3D11PixelShader** outPS);
}