#pragma once
#include "EnemyComponent.h"

//need SquareCollider in the owner
class GoombaComponent : public EnemyComponent
{
	void Init() override;
	void Update(float dt) override;
	void StepByPlayer(GameObject* other);

};

