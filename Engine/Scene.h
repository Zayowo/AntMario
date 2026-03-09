#pragma once
#include <iostream>
#include <vector>
#include "GameObject.h"

class Scene
{

public:
	void Init();
	void Update();
	void Render();
	void Destroy();

private:
	std::vector<GameObject*> gameObjects;

};