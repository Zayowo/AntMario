#pragma once
#include <GameObject.h>
class TurtleContext
{

public:
	GameObject* turtle;
	GameObject* player;

	float direction = -1.f;
	bool isHitByPlayer = false;
};

