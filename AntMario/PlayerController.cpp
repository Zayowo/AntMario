#include <Engine.h>
#include <Scene.h>
#include <GameObject.h>
#include <InputModule.h>
#include <ResourceModule.h>
#include <TimeModule.h>
#include <VelocityComponent.h>
#include <SpriteRenderer.h>
#include <SquareCollider.h>
#include "PlayerController.h"
#include "BonusComponent.h"
#include "InteractableBlockComponent.h"

void PlayerController::Init()
{

	inputModule = Engine::GetModule<InputModule>();
	if (!inputModule) std::cerr << "PlayerController: No InputModule detected!" << std::endl;

	// À éviter, mais c'est temporaire...
	gameController = owner->GetScene()->GetGameObjectsByName("GameController")[0]->GetComponent<GameController>();


	// Gestion du velocity
	velocityComponent = owner->GetComponent<VelocityComponent>();
	if (!velocityComponent) std::cerr << "PlayerController: No VelocityComponent detected!" << std::endl;

	velocityComponent->RegisterHit("Block", VelocityHitType::BOTTOM, [this](GameObject* block) { HitInteractableBlock(block); });
	velocityComponent->RegisterHit("Goomba", VelocityHitType::TOP, [this](GameObject* goomba) { StepOnGoomba(goomba);  });
	velocityComponent->RegisterHit("ReverseWalk", VelocityHitType::BOTTOM, [this](GameObject* block) { WalkUpsideDown(block); });


	// Gestion du collider
	collider = owner->GetComponent<SquareCollider>();
	if (!collider) std::cerr << "PlayerController: No SquareCollider detected!" << std::endl;

	collider->RegisterCallback("Bonus", [this](GameObject* coins) { PickUp(coins); });
	collider->RegisterCallback("BloodOrb", [this](GameObject* orb) { PickUp(orb); });

}

void PlayerController::Update(float dt)
{

	InputModule* inputModule = Engine::GetModule<InputModule>();
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

		else if (
			!isDoubleJump &&
			gameController->GetEnergy() >= 2.5f
		)
		{

			isDoubleJump = true;
			gameController->SetEnergy(gameController->GetEnergy() - 2.5f, 100.f);
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

	case (BonusType::BLOOD_ORB):
		gameController->SetEnergy(gameController->GetEnergy() + 5.f, 100.f);
		std::cout << "Player picked up a blood orb!" << std::endl;
		break;
	}

	bonus->GetScene()->DeleteGameObject(bonus);

}

void PlayerController::StepOnGoomba(GameObject* goomba)
{

	sf::Vector2f pos = goomba->GetTransform().pos + sf::Vector2f(0.f, -20.f);
	GameObject* orb = goomba->GetScene()->CreateGameObject("BloodOrb", pos);
	orb->AddComponent<SpriteRenderer>("Assets/BloodOrb.png");
	orb->AddComponent<SquareCollider>(sf::Vector2f(20.f, 20.f));
	orb->AddComponent<BonusComponent>(BonusType::BLOOD_ORB);

	goomba->GetScene()->DeleteGameObject(goomba);

	velocityComponent->SetY(-400.f);

}

void PlayerController::WalkUpsideDown(GameObject* block)
{

	if (gameController->GetEnergy() <= 0.f)
		return;

	if (isDoubleJump)
		return;

	float dt = Engine::GetModule<TimeModule>()->GetDeltaTime();
	gameController->SetEnergy(gameController->GetEnergy() - 5 * dt, 100.f);
	velocityComponent->SetY(-10.f);

}