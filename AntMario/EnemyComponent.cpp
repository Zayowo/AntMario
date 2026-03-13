#include "EnemyComponent.h"
#include <SquareCollider.h>
#include <Scene.h>
#include <VelocityComponent.h>

void EnemyComponent::Init()
{
	SquareCollider* collider = owner->GetComponent<SquareCollider>();
	collider->RegisterCallback("Fireball", [this](GameObject* o) {
		TouchByBall(o); });
}


void EnemyComponent::TouchByBall(GameObject* other) {
	owner->GetScene()->DeleteGameObject(owner);
}

void EnemyComponent::Move()
{
	VelocityComponent* velocity = owner->GetComponent<VelocityComponent>();
	velocity->SetX(-1.f);
}
