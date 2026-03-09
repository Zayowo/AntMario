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

GameObject* Scene::CreateGameObject(std::string name, sf::Vector2f pos)
{

	GameObject* gameObject = new GameObject(name, this);
	gameObject->GetTransform().pos = pos;
	gameObjects.push_back(gameObject);
	return gameObject;

}

void Scene::DeleteGameObject(GameObject* gameObject)
{

	if (gameObject->GetScene() != this)
		return;

	gameObjectsToDelete.push_back(gameObject);

}