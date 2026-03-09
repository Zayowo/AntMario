#include "GameObject.h"
#include "Component.h"

void GameObject::Init()
{

	for (Component* component : components)
		component->Init();

}


void GameObject::Update()
{

	for (Component* component : components)
		component->Update();

}

void GameObject::Render()
{

	for (Component* component : components)
		component->Render();

}

void GameObject::Destroy()
{

	for (Component* component : components)
		component->Destroy();

}

std::string GameObject::GetName()
{

	return name;

}

Transform& GameObject::GetTransform()
{

	return transform;

}
