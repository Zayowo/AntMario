#pragma once
#include "Component.h"
class FireComponent : public Component
{

public:
	void Init() override;
	void Update(float dt) override;

};