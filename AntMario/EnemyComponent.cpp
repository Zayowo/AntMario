#include "EnemyComponent.h"


void EnemyComponent::TouchByBall(GameObject* other) {
	owner->GetScene()->DeleteGameObject(owner);
}