#pragma once
#include <State.h>
#include "TurtleContext.h"

//need EnemyComponent
class InitialTurtle : public State<TurtleContext>
{
	void Enter(TurtleContext& ctx) override;
	void Execute(TurtleContext& ctx, float dt) override;
};

