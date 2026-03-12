#pragma once
#include <Component.h>

class PlayerController : public Component
{

public:
	void Init()override;
	void Update(float dt) override;

	void BreakBrick(GameObject* other);
	void PickUpCoin(GameObject* other);
	void StepOnGoomba(GameObject* other);

};