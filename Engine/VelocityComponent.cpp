#include "VelocityComponent.h"

VelocityComponent::VelocityComponent(float speed) : speed(speed) {};

void VelocityComponent::Update(float dt)
{

	Transform& transform = owner->GetTransform();
	transform.pos += velocity * speed * dt;
	
	if (velocity.y != 0.0f)
		velocity.y += 50 * dt;

}

void VelocityComponent::SetVelocity(sf::Vector2f velocity)
{

	this->velocity = velocity;

}

void VelocityComponent::SetX(float x)
{

	velocity.x = x;

}

void VelocityComponent::SetY(float y)
{

	velocity.y = y;

}