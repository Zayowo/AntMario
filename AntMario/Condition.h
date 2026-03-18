#pragma once
#include "PlayerContext.h"
#include "TurtleContext.h"

class Condition
{
public:
	//player
	static bool collisionWithEnemy(PlayerContext& p);
	static bool collitionWithFireBonus(PlayerContext& p);
	static bool collitionWithBigBonus(PlayerContext& p);

	static bool HasPickedFireFlower(PlayerContext& ctx);
	static bool IsHitByEnemy(PlayerContext& ctx);

	//turtle 
	static bool IsHitByPlayer(TurtleContext& ctx);
};

