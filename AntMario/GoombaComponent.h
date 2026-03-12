#pragma once
#include <Component.h>

//need SquareCollider in the owner
class GoombaComponent : public Component
{
	void Init() override;
	void Update(float dt) override;

	void TouchByBall(GameObject* other);
	void StepByPlayer(GameObject* other);

};

