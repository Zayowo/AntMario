#pragma once
#include <State.h>
#include "TurtleContext.h"

class InitialTurtle : public State<TurtleContext>
{
	void Execute(TurtleContext&, float dt) override;
};

