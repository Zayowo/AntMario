#include "FixedCameraComponent.h"

FixedCameraComponent::FixedCameraComponent(sf::Vector2f size, float minX, float maxX) :
	view(sf::Vector2f(0.f, 0.f), size),
	minX(minX),
	maxX(maxX)
{};

void FixedCameraComponent::Update(float dt)
{

    Transform& transform = owner->GetTransform();
    float smoothSpeed = 3.5f;

    float targetX = transform.pos.x;
    float targetY = transform.pos.y + 120.f;

    float newX = view.getCenter().x + (targetX - view.getCenter().x) * smoothSpeed * dt;
    newX = std::clamp(newX, minX, maxX);

    float newY = view.getCenter().y + (targetY - view.getCenter().y) * smoothSpeed * dt;
    newY = std::clamp(newY, 350.f, 450.f);

    view.setCenter(sf::Vector2f(newX, newY));

}

void FixedCameraComponent::Render(sf::RenderWindow* window)
{

	window->setView(view);

}