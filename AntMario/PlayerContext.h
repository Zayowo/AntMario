#pragma once
#include <GameObject.h>
#include "Bonus.h"
class PlayerContext
{

public:
	GameObject* player;
	float invulnerability = 0.f;
	bool isInMushroom = false;
	bool isInFireFlower = false;
	bool hasPickedMushroom = false;
	bool hasPickedFireFlower = false;
	bool isHitByEnemy = false;
};

