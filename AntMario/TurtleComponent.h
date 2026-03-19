#pragma once
#include "EnemyComponent.h"

//need FSMComponent<PiranhaContext>
class TurtleComponent : public EnemyComponent
{
	void Init() override;
	void Update(float dt) override;
	void StepByPlayer(GameObject* other);
	void ChangeDirection(float dir);
	void Destroy() override;
};

