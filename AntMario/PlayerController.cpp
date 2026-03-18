#include <Engine.h>
#include <Scene.h>
#include <GameObject.h>
#include <InputModule.h>
#include <SceneModule.h>
#include <ResourceModule.h>
#include <TimeModule.h>
#include <VelocityComponent.h>
#include <SpriteRenderer.h>
#include <SquareCollider.h>
#include <Utils.h>
#include "PlayerController.h"
#include "BonusComponent.h"
#include "InteractableBlockComponent.h"
#include "LittleState.h"
#include "BigState.h"
#include "FireState.h"
#include "Condition.h"

void PlayerController::Init()
{

	inputModule = Engine::GetModule<InputModule>();
	if (!inputModule) std::cerr << "PlayerController: No InputModule detected!" << std::endl;


	// À éviter, mais c'est temporaire...
	gameController = owner->GetScene()->GetGameObjectsByName("GameController")[0]->GetComponent<GameController>();
	coins = gameController->GetCoins();
	energy = gameController->GetEnergy();


	// Initialisation des stats du FSM du joueur
	fsm = owner->GetComponent<FSMComponent<PlayerContext>>();
	fsm->GetContext().player = owner;
	auto littleState = fsm->CreateState<LittleState>();
	auto bigState = fsm->CreateState<BigState>();
	auto fireState = fsm->CreateState<FireState>();

	littleState->AddTransition(Condition::HasPickedMushroom, bigState);
	littleState->AddTransition(Condition::HasPickedFireFlower, fireState);
	littleState->AddTransition([this](PlayerContext& ctx)
		{

			if (Condition::IsHitByEnemy(ctx))
				Engine::GetModule<SceneModule>()->SetScene("MainMenuScene");
			return false;

		}, nullptr);
	bigState->AddTransition(Condition::HasPickedFireFlower, fireState);
	bigState->AddTransition(Condition::IsHitByEnemy, littleState);
	fireState->AddTransition(Condition::IsHitByEnemy, littleState);

	fsm->Init(littleState);

	// Gestion du velocity
	velocityComponent = owner->GetComponent<VelocityComponent>();
	if (!velocityComponent) std::cerr << "PlayerController: No VelocityComponent detected!" << std::endl;

	velocityComponent->RegisterHit("Block", VelocityHitType::BOTTOM, [this](GameObject* block) { HitInteractableBlock(block); });

	velocityComponent->RegisterHit("Goomba", VelocityHitType::TOP, [this](GameObject* goomba) { StepOnGoomba(goomba);  });
	velocityComponent->RegisterHit("Goomba", VelocityHitType::LEFT, [this](GameObject* goomba) { HitByEnemy(goomba);  });
	velocityComponent->RegisterHit("Goomba", VelocityHitType::RIGHT, [this](GameObject* goomba) { HitByEnemy(goomba);  });
	velocityComponent->RegisterHit("Goomba", VelocityHitType::BOTTOM, [this](GameObject* goomba) { HitByEnemy(goomba);  });

	velocityComponent->RegisterHit("Turtle", VelocityHitType::TOP, [this](GameObject* turtle) { StepOnGoomba(turtle);  });
	velocityComponent->RegisterHit("Turtle", VelocityHitType::LEFT, [this](GameObject* turtle) { HitByEnemy(turtle);  });
	velocityComponent->RegisterHit("Turtle", VelocityHitType::RIGHT, [this](GameObject* turtle) { HitByEnemy(turtle);  });
	velocityComponent->RegisterHit("Turtle", VelocityHitType::BOTTOM, [this](GameObject* turtle) { HitByEnemy(turtle);  });

	velocityComponent->RegisterHit("Piranha", VelocityHitType::TOP, [this](GameObject* piranha) { HitByEnemy(piranha);  });
	velocityComponent->RegisterHit("Piranha", VelocityHitType::LEFT, [this](GameObject* piranha) { HitByEnemy(piranha);  });
	velocityComponent->RegisterHit("Piranha", VelocityHitType::RIGHT, [this](GameObject* piranha) { HitByEnemy(piranha);  });
	velocityComponent->RegisterHit("Piranha", VelocityHitType::BOTTOM, [this](GameObject* piranha) { HitByEnemy(piranha);  });

	velocityComponent->RegisterHit("ReverseWalk", VelocityHitType::BOTTOM, [this](GameObject* block) { WalkUpsideDown(block); });


	// Gestion du collider
	collider = owner->GetComponent<SquareCollider>();
	if (!collider) std::cerr << "PlayerController: No SquareCollider detected!" << std::endl;

	collider->RegisterCallback("Bonus", [this](GameObject* bonus) { PickUp(bonus); });
	collider->RegisterCallback("BloodOrb", [this](GameObject* orb) { PickUp(orb); });


}

void PlayerController::Update(float dt)
{

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
			*energy >= 0.05f
		)
		{

			isDoubleJump = true;
			*energy -= 0.05f;
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
		(*coins)++;
		Engine::GetModule<ResourceModule>()->PlaySound("Assets/Sounds/Coin.wav", 0.75f, 1.f);
		blockComponent->SetUsed(true);
		LogPrint("Player hit a coins block!");
		break;

	case (InteractableBlockType::MUSHROOM):
		blockComponent->SetUsed(true);
		LogPrint("Player hit a mushroom block!");
		break;
	case (InteractableBlockType::FIRE_FLOWER):
		blockComponent->SetUsed(true);
		LogPrint("Player hit a fire block!");
		break;

	case (InteractableBlockType::BRICK):
		Engine::GetModule<ResourceModule>()->PlaySound("Assets/Sounds/Brick.wav", 0.75f, 1.f);
		block->GetScene()->DeleteGameObject(block);
		LogPrint("Player hit a brick block!");
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
		(*coins)++;
		Engine::GetModule<ResourceModule>()->PlaySound("Assets/Sounds/Coin.wav", 0.75f, 1.f);
		LogPrint("Player picked up coins!");
		break;

	case (BonusType::BLOOD_ORB):
		*energy += 0.15f;
		LogPrint("Player picked up a blood orb!");
		break;

	case (BonusType::MUSHROOM):
	{
		auto& ctx = fsm->GetContext();
		if (!ctx.hasPickedMushroom)
			fsm->GetContext().hasPickedMushroom = true;
		LogPrint("Player picked up a Mushroom!");
		break;
	}

	case (BonusType::FIRE_FLOWER):
		fsm->GetContext().hasPickedFireFlower = true;
		LogPrint("Player picked up a FireFlower!");
		break;

	default:
		break;

	}

	bonus->GetScene()->DeleteGameObject(bonus);

}

void PlayerController::StepOnGoomba(GameObject* goomba)
{

	if (*energy <= 0.f)
		return;

	goomba->GetScene()->DeleteGameObject(goomba);

	float dt = Engine::GetModule<TimeModule>()->GetDeltaTime();
	*energy -= 0.05f * dt;
	velocityComponent->SetY(0.f);
	owner->GetTransform().pos.y = block->GetTransform().pos.y + 90.f;

	if (*energy <= 0.f)
		*energy = 0.f;

}


void PlayerController::StepOnTurtle(GameObject* turtle)
{
	sf::Vector2f pos = turtle->GetTransform().pos + sf::Vector2f(0.f, -20.f);
	GameObject* orb = turtle->GetScene()->CreateGameObject("BloodOrb", pos);
	orb->AddComponent<SpriteRenderer>("Assets/BloodOrb.png");
	orb->AddComponent<SquareCollider>(sf::Vector2f(20.f, 20.f));
	orb->AddComponent<BonusComponent>(BonusType::BLOOD_ORB);

	turtle->GetScene()->DeleteGameObject(turtle);

	velocityComponent->SetY(-400.f);

}

void PlayerController::EliminationPiranha(GameObject* piranha)
{
	sf::Vector2f pos = piranha->GetTransform().pos + sf::Vector2f(0.f, -20.f);
	GameObject* orb = piranha->GetScene()->CreateGameObject("BloodOrb", pos);
	orb->AddComponent<SpriteRenderer>("Assets/BloodOrb.png");
	orb->AddComponent<SquareCollider>(sf::Vector2f(20.f, 20.f));
	orb->AddComponent<BonusComponent>(BonusType::BLOOD_ORB);

	piranha->GetScene()->DeleteGameObject(piranha);

	velocityComponent->SetY(-400.f);
}

void PlayerController::KillEnemy(GameObject* enemy)
{

	auto enemyComponent = enemy->GetComponent<EnemyComponent>();
	if (enemyComponent)
		enemyComponent->Kill();

}

void PlayerController::HitByEnemy(GameObject* enemy)
{

	fsm->GetContext().isHitByEnemy = true;
	LogPrint("Je me suis fait tapé");

}