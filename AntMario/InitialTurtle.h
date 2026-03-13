#pragma once
#include <State.h>
#include "TurtleContext.h"

//need EnemyComponent
class InitialTurtle : public State<TurtleContext>
{
	void Execute(TurtleContext&, float dt) override;
};

