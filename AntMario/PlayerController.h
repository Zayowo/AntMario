#pragma once
#include <Component.h>

class PlayerController : public Component
{

public:

	void Init()override;
	void Update(float dt) override;

};