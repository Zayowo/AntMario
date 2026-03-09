#pragma once
#include <iostream>
#include <vector>
#include "GameObject.h"

class Scene
{

public:
	void Init();
	void Update(float dt);
	void Render(sf::RenderWindow* window);
	void Destroy();

	// Crée un game object dans la scène
	GameObject* CreateGameObject(std::string name, sf::Vector2f pos);

	// Supprime un game object de la scène
	void DeleteGameObject(GameObject* gameObject);

private:
	std::vector<GameObject*> gameObjects;
	std::vector<GameObject*> gameObjectsToDelete;

};