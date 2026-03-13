#include <Engine.h>
#include <Scene.h>
#include <GameObject.h>
#include <InputModule.h>
#include <ResourceModule.h>
#include <VelocityComponent.h>
#include <SquareCollider.h>
#include "PlayerController.h"
#include "BonusComponent.h"
#include "InteractableBlockComponent.h"

void PlayerController::Init()
{

	// À éviter, mais c'est temporaire...
	gameController = owner->GetScene()->GetGameObjectsByName("GameController")[0]->GetComponent<GameController>();

	VelocityComponent* velocityComponent = owner->GetComponent<VelocityComponent>();
	velocityComponent->RegisterHit("Block", VelocityHitType::BOTTOM, [this](GameObject* block) { HitInteractableBlock(block); });

	SquareCollider* collider = owner->GetComponent<SquareCollider>();
	collider->RegisterCallback("Bonus", [this](GameObject* coins) { PickUp(coins); });

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

void PlayerController::HitInteractableBlock(GameObject* block)
{

	InteractableBlockComponent* blockComponent = block->GetComponent<InteractableBlockComponent>();

	if (!blockComponent)
		return;

	if (blockComponent->IsUsed())
		return;

	switch (blockComponent->GetType())
	{
	case (InteractableBlockType::COINS):

		gameController->SetCoins(gameController->GetCoins() + 1);
		Engine::GetModule<ResourceModule>()->PlaySound("Assets/Sounds/Coin.wav", 0.75f, 1.f);
		blockComponent->SetUsed(true);
		std::cout << "Player hit a coins block!" << std::endl;
		break;

	case (InteractableBlockType::BRICK):
		Engine::GetModule<ResourceModule>()->PlaySound("Assets/Sounds/Brick.wav", 0.75f, 1.f);
		block->GetScene()->DeleteGameObject(block);
		std::cout << "Player hit a brick block!" << std::endl;
		break;

	default:
		break;
	}

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