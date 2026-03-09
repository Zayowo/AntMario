#include "Scene.h"

void Scene::Init()
{

	for (GameObject* gameObject : gameObjects)
		gameObject->Init();

}

void Scene::Update(float dt)
{

	for (GameObject* gameObject : gameObjects)
		gameObject->Update(dt);

}

void Scene::Render(sf::RenderWindow* window)
{

	for (GameObject* gameObject : gameObjects)
		gameObject->Render(window);

}

void Scene::Destroy()
{

	for (GameObject* gameObject : gameObjects)
		gameObject->Destroy();

}