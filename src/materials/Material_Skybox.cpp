#include "Material_Skybox.h"

Material_Skybox::Material_Skybox(std::string name, Renderer& renderer, std::string vShaderFilename, std::string pShaderFilename, Texture* texture)
	: Material(name, renderer, vShaderFilename, pShaderFilename, texture)
{

}
