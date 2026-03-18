#include "TurtleComponent.h"
#include <VelocityComponent.h>
#include <SquareCollider.h>
#include <Scene.h>

void TurtleComponent::Init()
{
	EnemyComponent::Init();
	SquareCollider* collider = owner->GetComponent<SquareCollider>();

}

void TurtleComponent::Update(float dt)
{
	VelocityComponent* velocity = owner->GetComponent<VelocityComponent>();
	velocity->SetX(-1.f);
}

void TurtleComponent::StepByPlayer(GameObject* other)
{
	VelocityComponent* otherVelocityComponent = other->GetComponent<VelocityComponent>();
	otherVelocityComponent->SetY(-350.f);
	owner->GetScene()->CreateGameObject(owner);
	owner->GetScene()->DeleteGameObject(owner);
}

void TurtleComponent::Destroy()
{
}
