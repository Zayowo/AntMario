#pragma once
#include "Component.h"
class FireComponent : public Component
{
private:
	void Init() override;
	void Update(float dt) override;
	void touchGround();
};

