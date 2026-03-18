#pragma once
#include "EnemyComponent.h"

class TurtleComponent : public EnemyComponent
{
	void Init() override;
	void Update(float dt) override;
	void StepByPlayer(GameObject* other);
	void Destroy() override;
};

