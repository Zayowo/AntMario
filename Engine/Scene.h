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

private:
	std::vector<GameObject*> gameObjects;

};