#include "InitialTurtle.h"

void InitialTurtle::Enter(PlayerContext&)
{
}

void InitialTurtle::Execute(PlayerContext&, float dt)
{
	VelocityComponent* velocity = owner->GetComponent<VelocityComponent>();
	velocity->SetX(-1.f);
}

void InitialTurtle::Exit(PlayerContext&)
{
}
