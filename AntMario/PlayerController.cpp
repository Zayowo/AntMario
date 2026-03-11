#include <Engine.h>
#include <GameObject.h>
#include <InputModule.h>
#include <VelocityComponent.h>
#include <SquareCollider.h>
#include "PlayerController.h"

void PlayerController::Update(float dt)
{

	InputModule* inputModule = Engine::GetModule<InputModule>();
	VelocityComponent* velocityComponent = owner->GetComponent<VelocityComponent>();
	Transform& transform = owner->GetTransform();

	sf::Vector2f velocity(0.0f, 0.0f);

	if (inputModule->Is(sf::Keyboard::Key::Q, InputState::HELD))
		velocity.x += -1.f;

	if (inputModule->Is(sf::Keyboard::Key::D, InputState::HELD))
		velocity.x += 1.f;

	velocityComponent->SetVelocity(velocity);
	if (velocity.x != 0.f)
		transform.scale.x = velocity.x > 0.f ? 1.f : -1.f;

}