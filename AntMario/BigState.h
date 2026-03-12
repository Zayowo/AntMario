#pragma once
#include <State.h>
#include "PlayerContext.h"
class BigState : public State<PlayerContext>
{
public:
	void Enter(PlayerContext& ctxP) override;
	void Execute(PlayerContext& ctxP, float dt) override;
	void Exit(PlayerContext& ctxP) override;
};

