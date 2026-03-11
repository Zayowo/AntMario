#include "Scene.h"
#include "GameObject.h"

void Scene::Init()
{

	for (GameObject* gameObject : gameObjects)
		gameObject->Init();

}

void Scene::Update(float dt)
{

	// Ajoute les game objects dans la liste
	for (GameObject* gameObjectToCreate : gameObjectsToCreate)
		gameObjects.emplace_back(gameObjectToCreate);

	for (GameObject* gameObjectToCreate : gameObjectsToCreate)
		gameObjectToCreate->Init();

	gameObjectsToCreate.clear();
	gameObjectsToCreate.shrink_to_fit();

	for (GameObject* gameObject : gameObjects)
		gameObject->Update(dt);

	if (gameObjectsToDelete.size() > 0) {

		for (GameObject* gameObject : gameObjectsToDelete) {

			auto it = std::find(gameObjects.begin(), gameObjects.end(), gameObject);
			if (it != gameObjects.end()) {
				std::iter_swap(it, gameObjects.end() - 1);
				gameObjects.pop_back();
			}

			gameObject->Destroy();
			delete gameObject;

		}

		gameObjectsToDelete.clear();

	}

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
	gameObjectsToCreate.emplace_back(gameObject);
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
			gameObjectsByName.push_back(gameObject);

	return gameObjectsByName;

}