#pragma once
#include <Scene.h>
#include <TimeModule.h>
#include <SpriteRenderer.h>
#include <VelocityComponent.h>
#include <SquareCollider.h>
#include <ButtonRenderer.h>
#include <Json.h>
#include <iostream>
#include <fstream>
#include "BackgroundElement.h"
#include "FixedCameraComponent.h"
#include "PlayerController.h"
#include "BonusComponent.h"
#include "GameController.h"

using json = nlohmann::json;

class PrototypeScene : public Scene
{

public:
	PrototypeScene()
	{

		std::ifstream file("Assets/Level/AntLevel_6.json");
		json data;
		file >> data;

		float levelWidth = data["metadata"]["width"];
		float gridSize = data["metadata"]["tileSize"];

		GameObject* sky = CreateGameObject("Sky", { 600, 400 });
		sky->GetTransform().scale = sf::Vector2f(2.4f, 2.f);
		sky->AddComponent<BackgroundElement>("Assets/Environment/Background.png", 1.f, sf::Vector2f(-900.f, 0.f));

		GameObject* sky1 = CreateGameObject("Sky", { 600, 400 });
		sky1->GetTransform().scale = sf::Vector2f(2.4f, 2.f);
		sky1->AddComponent<BackgroundElement>("Assets/Environment/Background.png", 1.f, sf::Vector2f(-300.f, 0.f));

		GameObject* player = CreateGameObject("Player", { 150, 700 });
		player->GetTransform().scale = sf::Vector2f(0.45f, 0.45f);
		player->GetTransform().origin = sf::Vector2f(0.5f, 1.f);
		player->AddComponent<FixedCameraComponent>(sf::Vector2f(1200.f, 800.f), 600.f, levelWidth - 600.f);
		player->AddComponent<SpriteRenderer>("Assets/Player.png");
		player->AddComponent<PlayerController>();
		player->AddComponent<VelocityComponent>(260.f);
		player->AddComponent<SquareCollider>(sf::Vector2f(70.f, 140.f));


		for (const auto& tile : data["tiles"])
		{

			std::string tileType = tile["type"];
			float xPos = tile["x"] * gridSize;
			float yPos = tile["y"] * gridSize;
			float width = tile["w"];
			float height = tile["h"];

			if (tileType == "Terrain")
			{

				GameObject* collider = CreateGameObject("Collider", { xPos, yPos });
				collider->GetTransform().origin = sf::Vector2f(0.f, 0.f);
				collider->AddComponent<SquareCollider>(sf::Vector2f(width * gridSize, height * gridSize));
				SpriteRenderer* colliderSprite = collider->AddComponent<SpriteRenderer>("Assets/Environment/Block.png");
				colliderSprite->SetTiling(sf::Vector2f(width * gridSize, height * gridSize), true);

			}

			if (tileType == "Brick")
			{

				GameObject* brick = CreateGameObject("Brick", { xPos, yPos });
				brick->GetTransform().origin = sf::Vector2f(0.f, 0.f);
				brick->AddComponent<SquareCollider>(sf::Vector2f(width * gridSize, height * gridSize));
				brick->AddComponent<SpriteRenderer>("Assets/Environment/Brick.png");

			}

			if (tileType == "LuckyCoin")
			{

				GameObject* coin = CreateGameObject("Coins", { xPos + gridSize * 0.5f, yPos + gridSize * 0.5f });
				coin->AddComponent<SquareCollider>(sf::Vector2f(40.f, 40.f));
				coin->AddComponent<BonusComponent>(BonusType::COINS);

			}

		}

		GameObject* gameController = CreateGameObject("GameController", { 0.f, 0.f });
		gameController->AddComponent<GameController>();

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