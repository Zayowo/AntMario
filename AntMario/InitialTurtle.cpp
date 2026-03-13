#include "InitialTurtle.h"
#include "EnemyComponent.h"
#include <VelocityComponent.h>


void InitialTurtle::Execute(TurtleContext& t, float dt)
{
	t.turtle->GetComponent<EnemyComponent>()->Move();
}

