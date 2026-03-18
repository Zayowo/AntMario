#pragma once
#include <VelocityComponent.h>
#include "EnemyComponent.h"

//need SquareCollider in the owner
class GoombaComponent : public EnemyComponent
{

public:
	void Init() override;
	void Update(float dt) override;
	void StepByPlayer(GameObject* other);
	void ChangeDirection(float direction);

private:
	VelocityComponent* velocityComponent;
	float direction = -1.f;

};

