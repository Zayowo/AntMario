#include "GoombaComponent.h"
#include <VelocityComponent.h>

void GoombaComponent::Update(float dt)
{
	VelocityComponent* velocity = owner->GetComponent<VelocityComponent>();

	velocity->SetVelocity(sf::Vector2f(-1.f, 0.f));
}
