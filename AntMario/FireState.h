#pragma once
#include <State.h>
#include "PlayerContext.h"
class FireState : public State<PlayerContext>
{
	void Enter(PlayerContext& p) override;
	void Execute(PlayerContext& p, float dt) override;
};

