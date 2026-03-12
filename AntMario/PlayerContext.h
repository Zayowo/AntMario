#pragma once
#include <GameObject.h>
#include "Bonus.h"
class PlayerContext
{

public:
	GameObject* player;
	float invulnerability = 0.f;
	std::vector<GameObject*> enemies;
	std::vector<GameObject*> bonuses;
};

