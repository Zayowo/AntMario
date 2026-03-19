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

	static bool HasPickedMushroom(PlayerContext& ctx);
	static bool HasPickedFireFlower(PlayerContext& ctx);
	static bool IsHitByEnemy(PlayerContext& ctx);

	//turtle 
	static bool IsHitByPlayer(TurtleContext& ctx);
	static bool IsTurtleInInitialState(GameObject* turtle);
	static bool IsTurtleInShellWithoutMoving(GameObject* turtle);
};

