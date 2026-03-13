#pragma once
#include <Scene.h>
#include <SpriteRenderer.h>
#include <VelocityComponent.h>
#include <SquareCollider.h>
#include <ButtonRenderer.h>
#include <Json.h>
#include "BackgroundElement.h"
#include "FixedCameraComponent.h"
#include "PlayerController.h"
#include "Bonus.h"
#include <iostream>
#include <fstream>
#include "FSMComponent.h"
#include "PlayerContext.h"
#include "LittleState.h"
#include "GoombaComponent.h"
#include "BigState.h"
#include "FireState.h"
#include "Condition.h"
#include "PiranhaComponent.h"
#include "TurtleContext.h"
#include "InitialTurtle.h"
#include "ShellTurtle.h"

using json = nlohmann::json;

class PrototypeScene : public Scene
{

public:
	PrototypeScene()
	{

		//GameObject* sky = CreateGameObject("Sky", { 600, 400 });
		//sky->GetTransform().scale = sf::Vector2f(2.4f, 2.f);
		//sky->AddComponent<BackgroundElement>("Assets/Environment/Background.png", 1.f, sf::Vector2f(-900.f, 0.f));

		//GameObject* sky1 = CreateGameObject("Sky", { 600, 400 });
		//sky1->GetTransform().scale = sf::Vector2f(2.4f, 2.f);
		//sky1->AddComponent<BackgroundElement>("Assets/Environment/Background.png", 1.f, sf::Vector2f(-300.f, 0.f));

		GameObject* player = CreateGameObject("Player", { 150, 700 });
		player->GetTransform().scale = sf::Vector2f(1.f, 0.75f);
		player->GetTransform().origin = sf::Vector2f(0.5f, 1.f);
		player->AddComponent<FixedCameraComponent>(sf::Vector2f(1200.f, 800.f), 600.f, 1000.f);
		player->AddComponent<SpriteRenderer>("Assets/PlayerSprite.png");
		player->AddComponent<PlayerController>();
		player->AddComponent<VelocityComponent>(260.f);
		player->AddComponent<SpriteRenderer>("Assets/PlayerSprite.png");
		player->AddComponent<SquareCollider>(sf::Vector2f(40.f, 60.f));

		std::ifstream file("Assets/Level/AntLevel_2.json");
		json data;
		file >> data;

		for (const auto& tile : data["tiles"])
		{

			std::string tileType = tile["type"];
			float xPos = tile["x"] * 40.f;
			float yPos = tile["y"] * 40.f;
			float width = tile["w"];
			float height = tile["h"];

			if (tileType == "Terrain")
			{

				GameObject* collider = CreateGameObject("Collider", { xPos, yPos });
				collider->GetTransform().origin = sf::Vector2f(0.f, 0.f);
				collider->AddComponent<SquareCollider>(sf::Vector2f(width * 40.f, height * 40.f));

			}

			if (tileType == "Brick")
			{

				GameObject* collider = CreateGameObject("Brick", { xPos, yPos });
				collider->GetTransform().origin = sf::Vector2f(0.f, 0.f);
				collider->AddComponent<SquareCollider>(sf::Vector2f(width * 40.f, height * 40.f));

			}

		}
		GameObject* coin = CreateGameObject("Coins", { 210, 600 });
		coin->AddComponent<Bonus>(BonusType::Coins);
		coin->AddComponent<SquareCollider>(sf::Vector2f(40.f, 40.f));

		GameObject* bonus1 = CreateGameObject("Bonus1", { 240, 600 });
		bonus1->AddComponent<Bonus>(BonusType::Bonus1);
		bonus1->AddComponent<SquareCollider>(sf::Vector2f(40.f, 40.f));

		GameObject* bonus2 = CreateGameObject("Bonus2", { 310, 600 });
		bonus2->AddComponent<Bonus>(BonusType::Bonus2);
		bonus2->AddComponent<SquareCollider>(sf::Vector2f(40.f, 40.f));

		GameObject* bonus3 = CreateGameObject("Bonus3", { 400, 600 });
		bonus3->AddComponent<Bonus>(BonusType::Bonus3);
		bonus3->AddComponent<SquareCollider>(sf::Vector2f(40.f, 40.f));

		FSMComponent<PlayerContext>* fsmPlayer = player->AddComponent<FSMComponent<PlayerContext>>();
		PlayerContext& ctxPlayer = fsmPlayer->GetContext();
		ctxPlayer.player = player;

		//add bonus in context

		//ALL STATE :
		LittleState* littleState = fsmPlayer->CreateState<LittleState>();
		BigState* bigState = fsmPlayer->CreateState<BigState>();
		FireState* fireState = fsmPlayer->CreateState<FireState>();


		//little state transition
		littleState->AddTransition(Condition::collitionWithFireBonus, fireState);
		littleState->AddTransition(Condition::collitionWithBigBonus, bigState);

		//bigstate transition
		bigState->AddTransition(Condition::collisionWithEnemy, littleState);
		bigState->AddTransition(Condition::collitionWithFireBonus, fireState);

		//firestate transition
		fireState->AddTransition(Condition::collisionWithEnemy, littleState);
		
		fsmPlayer->Init(fireState);
		

		// enemy
		GameObject* goomba = CreateGameObject("Goomba", { 600, 700 });
		goomba->GetTransform().origin = sf::Vector2f(0.5f, 1.f);
		goomba->AddComponent<GoombaComponent>();
		goomba->AddComponent<VelocityComponent>(90.f);
		goomba->AddComponent<SpriteRenderer>("Assets/PlayerSprite.png");
		goomba->AddComponent<SquareCollider>(sf::Vector2f(40.f, 60.f));


		GameObject* piranha = CreateGameObject("Piranha", { 700, 720 });
		piranha->AddComponent<PiranhaComponent>();
		piranha->AddComponent<SpriteRenderer>("Assets/PlayerSprite.png");
		piranha->AddComponent<SquareCollider>(sf::Vector2f(40.f, 60.f));

		
		GameObject* turtle = CreateGameObject("Turtle", { 700, 720 });
		turtle->AddComponent<EnemyComponent>();
		turtle->AddComponent<SquareCollider>();
		FSMComponent<TurtleContext>* fsmTurtle = turtle->AddComponent<FSMComponent<TurtleContext>>();
		TurtleContext ctxTurtle = fsmTurtle->GetContext();
		ctxTurtle.player = player;
		ctxTurtle.turtle = turtle;
		//State turtle
		InitialTurtle* initTurtle = fsmTurtle->CreateState<InitialTurtle>();
		ShellTurtle* shellTurtle = fsmTurtle->CreateState<ShellTurtle>();

		//initTurtle->AddTransition(shellTurtle);

		fsmTurtle->Init(initTurtle);



	};

	void Update(float dt) override
	{

		InputModule* inputModule = Engine::GetModule<InputModule>();
		SceneModule* sceneModule = Engine::GetModule<SceneModule>();

		if (inputModule->Is(sf::Keyboard::Key::Escape, InputState::PRESSED))
			sceneModule->PushScene("PauseScene");

		Scene::Update(dt);

	}

};