#pragma once
#include "PlayerContext.h"
class Condition
{
public:
	static bool collisionWithEnemy(PlayerContext& p);
	static bool collitionWithFireBonus(PlayerContext& p);
	static bool collitionWithBigBonus(PlayerContext& p);

	static bool HasPickedMushroom(PlayerContext& ctx);
	static bool HasPickedFireFlower(PlayerContext& ctx);
	static bool IsHitByEnemy(PlayerContext& ctx);
};

