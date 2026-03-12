#include <Engine.h>
#include <Scene.h>
#include <GameObject.h>
#include <InputModule.h>
#include <ResourceModule.h>
#include <VelocityComponent.h>
#include <SquareCollider.h>
#include "PlayerController.h"
#include "BonusComponent.h"

void PlayerController::Init()
{

	// À éviter, mais c'est temporaire...
	gameController = owner->GetScene()->GetGameObjectsByName("GameController")[0]->GetComponent<GameController>();

	VelocityComponent* velocityComponent = owner->GetComponent<VelocityComponent>();
	velocityComponent->RegisterHit("Brick", VelocityHitType::BOTTOM, [this](GameObject* brick) { BreakBrick(brick); });

	SquareCollider* collider = owner->GetComponent<SquareCollider>();
	collider->RegisterCallback("Coins", [this](GameObject* coin) { PickUp(coin); });


	// Ajout des collisions entre les oppenents et le joueur
	collider->RegisterCallback("opponent1", [this](GameObject* other) { BreakBrick(other); });
	collider->RegisterCallback("opponent2", [this](GameObject* other) { BreakBrick(other); });
	collider->RegisterCallback("opponent3", [this](GameObject* other) { BreakBrick(other); });
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

	if (inputModule->Is(sf::Keyboard::Key::Space, InputState::PRESSED))

	{

		if (velocityComponent->IsGrounded())
		{
			isDoubleJump = false;
			Engine::GetModule<ResourceModule>()->PlaySound("Assets/Sounds/Jump.wav", 0.75f, 1.f);
			velocityComponent->SetY(-840.f);
		}

		else if (!isDoubleJump)
		{

			isDoubleJump = true;
			Engine::GetModule<ResourceModule>()->PlaySound("Assets/Sounds/Jump.wav", 0.75f, 1.25f);
			velocityComponent->SetY(-840.f);

		}
	}

	velocityComponent->SetX(velocityX);
	if (velocityX != 0.f)
		transform.scale.x = abs(transform.scale.x) * (velocityX > 0.f ? 1 : -1);

}

void PlayerController::BreakBrick(GameObject* brick)
{

	Engine::GetModule<ResourceModule>()->PlaySound("Assets/Sounds/Brick.wav", 0.75f, 1.f);
	brick->GetScene()->DeleteGameObject(brick);

}

void PlayerController::PickUp(GameObject* bonus)
{

	BonusComponent* bonusComponent = bonus->GetComponent<BonusComponent>();
	
	if (!bonusComponent)
		return;

	switch (bonusComponent->GetType())
	{
	case (BonusType::COINS):
		gameController->SetCoins(gameController->GetCoins() + 1);
		Engine::GetModule<ResourceModule>()->PlaySound("Assets/Sounds/Coin.wav", 0.75f, 1.f);
		std::cout << "Player picked up coins!" << std::endl;
		break;
	}

	bonus->GetScene()->DeleteGameObject(bonus);

}