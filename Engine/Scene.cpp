#include "Scene.h"
#include "GameObject.h"

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
	gameObjects.emplace_back(gameObject);
	return gameObject;

}

void Scene::DeleteGameObject(GameObject* gameObject)
{

	if (gameObject->GetScene() != this)
		return;

	gameObjectsToDelete.emplace_back(gameObject);

}

std::vector<GameObject*> Scene::GetGameObjectsByName(std::string name)
{
	std::vector<GameObject*> gameObjectsByName;

	for (GameObject* gameObject : gameObjects)
		if (gameObject->GetName() == name)
			gameObjectsByName.emplace_back(gameObject);

	return gameObjectsByName;

}