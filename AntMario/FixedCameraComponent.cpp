#include "FixedCameraComponent.h"

FixedCameraComponent::FixedCameraComponent(sf::Vector2f size, float minX, float maxX) :
	view(sf::Vector2f(0.f, 0.f), size),
	minX(minX),
	maxX(maxX)
{};

void FixedCameraComponent::Update(float dt)
{

	Transform& transform = owner->GetTransform();
	float viewX = transform.pos.x;

	if (viewX < minX)
		viewX = minX;

	if (viewX > maxX)
		viewX = maxX;

	view.setCenter(sf::Vector2f(viewX, 400));

}

void FixedCameraComponent::Render(sf::RenderWindow* window)
{

	window->setView(view);

}