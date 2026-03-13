#pragma once
#include <Component.h>

class PiranhaComponent : public Component
{
private:
	void Init() override;
	void Update(float dt) override;
	void TouchByBall(GameObject* o);

	float max = 60.f;
	float y = 0.f;
	float yOrigin;
	float speed = 200.f;
	float cooldown = 0.f; // max 2 sec
	float cooldownMax = 2.f;
	bool isMoving = false;

	bool isOut = false;
};

