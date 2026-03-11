#pragma once
#include <iostream>
#include <vector>
#include "GameObject.h"

class Scene
{

public:
	bool isBreakingUpdate = false;
	
	virtual void Init();
	virtual void Update(float dt);
	virtual void Render(sf::RenderWindow* window);
	virtual void Destroy();

	// Crée un game object dans la scène
	GameObject* CreateGameObject(std::string name, sf::Vector2f pos);

	// Supprime un game object de la scène
	void DeleteGameObject(GameObject* gameObject);

	// Récupère les game objects avec un nom
	std::vector<GameObject*> GetGameObjectsByName(std::string name);

private:
	std::vector<GameObject*> gameObjects;
	std::vector<GameObject*> gameObjectsToCreate;
	std::vector<GameObject*> gameObjectsToDelete;

};