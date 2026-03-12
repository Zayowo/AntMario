#pragma once
#include "PlayerContext.h"
class Condition
{
public:
	static bool collisionWithEnemy(PlayerContext& p);
	static bool collitionWithFireBonus(PlayerContext& p);
	static bool collitionWithBigBonus(PlayerContext& p);
};

