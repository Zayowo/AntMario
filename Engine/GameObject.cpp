#include "GameObject.h"
#include "Component.h"

GameObject::GameObject(std::string name, Scene* scene) : name(name), scene(scene) {};

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

Scene* GameObject::GetScene()
{

	return scene;

}

Transform& GameObject::GetTransform()
{

	return transform;

}
