#include "InitialTurtle.h"
#include <VelocityComponent.h>


void InitialTurtle::Execute(TurtleContext& t, float dt)
{
	VelocityComponent* velocity = t.turtle->GetComponent<VelocityComponent>();
	
	if (velocity == nullptr)
		std::cerr << "TurtleComponent : missing VelocityComponent" << std::endl;

	velocity->SetX(-1.f);
}

