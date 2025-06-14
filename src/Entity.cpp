#include "Entity.h"



Entity::Entity(std::string entityName, Mesh** mesh, Material** material)
	: name(entityName), mesh(mesh), material(material)
{
}
