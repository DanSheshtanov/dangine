#pragma once

#include <DirectXMath.h>

#include "Material.h"

class Material_Skybox : public Material
{
public:
	Material_Skybox(std::string name, Renderer& renderer,
		std::string vShaderFilename, std::string pShaderFilename,
		Texture* texture);
protected:
	struct SkyboxCB : CBufferBase
	{
		DirectX::XMMATRIX WVP;
	};

};

