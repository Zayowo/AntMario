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