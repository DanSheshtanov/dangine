#pragma once
#include <string>

#include "Transform.h"

class Mesh;
class Material;

class Entity
{
public:
	Entity(std::string entityName, Mesh** mesh = nullptr, Material** material = nullptr);

	Transform transform;
	Mesh** mesh;
	Material** material;

	std::string GetName() { return name; }

private:
	std::string name;
};