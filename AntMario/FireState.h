#pragma once
#include <State.h>
#include "PlayerContext.h"
class FireState : public State<PlayerContext>
{
	void Enter(PlayerContext& ctx) override;
	void Execute(PlayerContext& ctx, float dt) override;
	void Exit(PlayerContext& ctx) override;
};

