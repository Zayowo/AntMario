#include <Engine.h>
#include <GameObject.h>
#include <InputModule.h>
#include <VelocityComponent.h>
#include <SquareCollider.h>
#include "PlayerController.h"
#include <Scene.h>

void PlayerController::Init()
{
	VelocityComponent* velocityComponent = owner->GetComponent<VelocityComponent>();
	velocityComponent->RegisterHit("Brick", VelocityHitType::BOTTOM, [this](GameObject* other) { BreakBrick(other); });

	SquareCollider* collider = owner->GetComponent<SquareCollider>();
	collider->RegisterCallback("Coins", [this](GameObject* other) { PickUpCoin(other); });

}

void PlayerController::Update(float dt)
{

	InputModule* inputModule = Engine::GetModule<InputModule>();
	VelocityComponent* velocityComponent = owner->GetComponent<VelocityComponent>();
	Transform& transform = owner->GetTransform();

	float velocityX = 0.f;

	if (inputModule->Is(sf::Keyboard::Key::Q, InputState::HELD))
		velocityX += -1.f;

	if (inputModule->Is(sf::Keyboard::Key::D, InputState::HELD))
		velocityX += 1.f;

	if (inputModule->Is(sf::Keyboard::Key::LShift, InputState::HELD))
		velocityX *= 1.5f;

	if (
		velocityComponent->GetVelocity().y == 0.0f &&
		inputModule->Is(sf::Keyboard::Key::Space, InputState::HELD)
	)
		velocityComponent->SetY(-750.f);

	velocityComponent->SetX(velocityX);
	if (velocityX != 0.f)
		transform.scale.x = velocityX > 0.f ? 1.f : -1.f;

}

void PlayerController::BreakBrick(GameObject* other)
{

	other->GetScene()->DeleteGameObject(other);

}

void PlayerController::PickUpCoin(GameObject* other)
{

	other->GetScene()->DeleteGameObject(other);

}