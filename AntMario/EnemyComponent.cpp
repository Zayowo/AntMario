#include "EnemyComponent.h"
#include <SquareCollider.h>
#include <Scene.h>

void EnemyComponent::Init()
{
	SquareCollider* collider = owner->GetComponent<SquareCollider>();
	collider->RegisterCallback("Fireball", [this](GameObject* o) {
		TouchByBall(o); });
}

void EnemyComponent::TouchByBall(GameObject* other) {
	owner->GetScene()->DeleteGameObject(owner);
}