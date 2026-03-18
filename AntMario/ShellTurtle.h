#pragma once
#include <State.h>
#include "TurtleContext.h"
class ShellTurtle : public State<TurtleContext>
{
	void Enter(TurtleContext&) override;
	void Execute(TurtleContext& t, float dt) override;

	bool IsHitByPlayer(TurtleContext& ctx);

	bool isMoving = false;
};

