#pragma once
#include <State.h>
#include "TurtleContext.h"
class ShellTurtle : public State<TurtleContext>
{
	void Execute(TurtleContext& t, float dt) override;
};

