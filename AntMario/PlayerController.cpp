#include <Engine.h>
#include <InputModule.h>
#include <VelocityComponent.h>
#include <SquareCollider.h>
#include "PlayerController.h"
#include <GameObject.h>
#include <Scene.h>



void PlayerController::Init()
{
	SquareCollider* collider = owner->GetComponent<SquareCollider>();
	collider->RegisterCollisionCallback("Coins", [](GameObject* other) {

		other->GetScene()->DeleteGameObject(other);
		});
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

	if (inputModule->Is(sf::Keyboard::Key::Space, InputState::PRESSED))
		velocityComponent->SetY (-10.f);

	velocityComponent->SetX(velocityX);
	if (velocityX != 0.f)
		transform.scale.x = velocityX;



}