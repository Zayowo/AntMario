#pragma once
#include <Component.h>

class FixedCameraComponent : public Component
{

public:
	FixedCameraComponent(sf::Vector2f size);

	void Update(float dt);
	void Render(sf::RenderWindow* window);

private:
	sf::View view;

};