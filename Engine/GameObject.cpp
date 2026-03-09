#include "GameObject.h"

std::string GameObject::GetName()
{
	return name;
}

Transform& GameObject::GetTransform()
{
	return transform;
}
