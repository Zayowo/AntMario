#pragma once
#include "State.h"
#include "PlayerContext.h"

class LittleState : public State<PlayerContext>
{
public:
	void Enter(PlayerContext& pc) override;
	void Execute(PlayerContext& pc) override;
	void Exit(PlayerContext& pc) override;
};

