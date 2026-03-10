#pragma once
#include "Component.h"

class VelocityComponent : public Component
{

public:
	VelocityComponent(float speed);

	void Update(float dt) override;

	// Applique une vélocité
	void SetVelocity(sf::Vector2f velocity);

	// Applique une vélocité sur un axe x ou y
	void SetX(float x);
	void SetY(float y);

private:
	float speed;
	sf::Vector2f velocity = sf::Vector2f(0.f, 0.f);

};