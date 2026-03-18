#pragma once
#include <GameObject.h>
class TurtleContext
{

public:
	GameObject* turtle;
	GameObject* player;

	bool isHitByPlayer = false;
};

