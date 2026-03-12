#pragma once
#include <Component.h>

class FixedCameraComponent : public Component
{

public:
	FixedCameraComponent(sf::Vector2f size, float minX, float maxX);

	void Update(float dt);
	void Render(sf::RenderWindow* window);

private:
	sf::View view;
	float minX;
	float maxX;

};