#pragma once
#include <Component.h>

class FinishZoneComponent : public Component
{

public:
	void Init() override;
	void Update(float dt) override;

private:
	bool hasTriggered = false;

};
