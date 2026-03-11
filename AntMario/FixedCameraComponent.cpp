#include "FixedCameraComponent.h"

FixedCameraComponent::FixedCameraComponent(sf::Vector2f size) :
	view(sf::Vector2f(0.f, 0.f), size)
{};

void FixedCameraComponent::Update(float dt)
{

	Transform& transform = owner->GetTransform();
	view.setCenter(sf::Vector2f(transform.pos.x, 450));

}

void FixedCameraComponent::Render(sf::RenderWindow* window)
{

	window->setView(view);

}