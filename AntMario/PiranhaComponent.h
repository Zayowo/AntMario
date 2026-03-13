#pragma once
#include <Component.h>


class PiranhaComponent : public Component
{
private:
	void Init() override;
	void Update(float dt) override;

	float max = 60.f;
	float y = 0.f;
	float yOrigin;
	float speed = 200.f;
	float cooldown = 0.f; // max 3 sec
	bool isMove = false;
};

