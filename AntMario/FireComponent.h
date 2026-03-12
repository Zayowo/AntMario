#pragma once
#include "Component.h"
class FireComponent : public Component
{
private:
	void Init() override;
	void Update(float dt) override;
	sf::Vector2f baseVelocity = { 0.f, 0.f };
};

