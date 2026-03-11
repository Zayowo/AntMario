#pragma once
#include <GameObject.h>
class PlayerContext
{

public:
	GameObject* player;
	float invulnerability = 0.f;
	std::vector<GameObject*> enemies;
};

