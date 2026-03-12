#include "GoombaComponent.h"
#include <VelocityComponent.h>
#include <SquareCollider.h>
#include <Scene.h>

void GoombaComponent::Init() {

	SquareCollider* collider = owner->GetComponent<SquareCollider>();
	collider->RegisterCallback("Fireball", [this](GameObject* o) { TouchByBall(o); });
	
}

void GoombaComponent::Update(float dt)
{
	VelocityComponent* velocity = owner->GetComponent<VelocityComponent>();
	velocity->SetX(-1.f);
}


void GoombaComponent::TouchByBall(GameObject* other) {
	other->GetScene()->DeleteGameObject(other);
	owner->GetScene()->DeleteGameObject(owner);
}

void GoombaComponent::StepByPlayer(GameObject* other)
{
	VelocityComponent* otherVelocityComponent = other->GetComponent<VelocityComponent>();
	otherVelocityComponent->SetY(-350.f);
	owner->GetScene()->DeleteGameObject(owner);

}