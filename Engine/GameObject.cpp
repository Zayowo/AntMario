#include "GameObject.h"
#include "Component.h"

void GameObject::Init()
{

	for (Component* component : components)
		component->Init();

}


void GameObject::Update(float dt)
{

	for (Component* component : components)
		component->Update(dt);

}

void GameObject::Render(sf::RenderWindow* window)
{

	for (Component* component : components)
		component->Render(window);

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
