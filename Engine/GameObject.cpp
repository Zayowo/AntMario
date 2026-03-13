#include "GameObject.h"
#include "Component.h"
#include "Utils.h"

GameObject::GameObject(std::string name, Scene* scene) :
	name(name),
	scene(scene)
{};

void GameObject::Init()
{

	for (Component* component : components)
		component->Init();

}


void GameObject::Update(float dt)
{

	if (!isAlwaysLoaded && !IsLoaded(this))
		return;

	for (Component* component : components)
		component->Update(dt);

}

void GameObject::Render(sf::RenderWindow* window)
{

	if (!isAlwaysLoaded && !IsLoaded(this))
		return;

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

void GameObject::SetIsAlwaysLoaded(bool isAlwaysLoaded)
{

	this->isAlwaysLoaded = isAlwaysLoaded;

}