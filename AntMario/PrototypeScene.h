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
#include "InteractableBlockComponent.h"
#include "GameController.h"

using json = nlohmann::json;

class PrototypeScene : public Scene
{

public:
	PrototypeScene()
	{

		std::ifstream file("Assets/Level/AntLevel_7.json");
		json data;
		file >> data;

		float levelWidth = data["metadata"]["width"];
		float gridSize = data["metadata"]["tileSize"];

		GameObject* sky = CreateGameObject("Sky", { 600, 600 });
		sky->GetTransform().scale = sf::Vector2f(2.4f, 2.f);
		sky->AddComponent<BackgroundElement>("Assets/Environment/Background.png", 1.f, sf::Vector2f(-900.f, 0.f));

		GameObject* sky1 = CreateGameObject("Sky", { 600, 600 });
		sky1->GetTransform().scale = sf::Vector2f(2.4f, 2.f);
		sky1->AddComponent<BackgroundElement>("Assets/Environment/Background.png", 1.f, sf::Vector2f(-300.f, 0.f));

		GameObject* player = CreateGameObject("Player", { 150, 700 });
		player->GetTransform().scale = sf::Vector2f(0.55f, 0.55f);
		player->GetTransform().origin = sf::Vector2f(0.5f, 1.f);
		player->AddComponent<FixedCameraComponent>(sf::Vector2f(1000.f, 666.f), 500.f, levelWidth - 500.f);
		player->AddComponent<SpriteRenderer>("Assets/Player.png");
		player->AddComponent<PlayerController>();
		player->AddComponent<VelocityComponent>(220.f);
		player->AddComponent<SquareCollider>(sf::Vector2f(50.f, 135.f));


		for (const auto& tile : data["tiles"])
		{

			std::string tileType = tile["type"];
			float xPos = tile["x"] * gridSize;
			float yPos = tile["y"] * gridSize;
			float width = tile["w"];
			float height = tile["h"];

			if (tileType.find("T_") == 0 || tileType == "TERRAIN")
			{

				// En gros pour expliquer ce qui se passe, on va simplifier les collisions, mais les sprite seront malheureusement en un par un
				// C'est pas l'optimisation qu'on souhaite, ça doit être changer, mais c'est temporaire pour tester la tileset! :)

				for (int ix = 0; ix < (int)width; ix++)
				{
					for (int iy = 0; iy < (int)height; iy++)
					{
						float finalX = xPos + (ix * gridSize);
						float finalY = yPos + (iy * gridSize);

						// On crée un objet purement visuel (pas de collider = pas de calcul physique)
						GameObject* visualTile = CreateGameObject("TerrainTile", { finalX, finalY });
						visualTile->GetTransform().origin = sf::Vector2f(0.f, 0.f);

						SpriteRenderer* sprite = visualTile->AddComponent<SpriteRenderer>("Assets/Environment/Tileset.png");

						sf::IntRect uvRect;
						sf::Vector2i size(gridSize, gridSize);
						int g = static_cast<int>(gridSize);

						if (tileType == "T_TOP_LEFT")          uvRect = sf::IntRect(sf::Vector2i(0, 0), size);
						else if (tileType == "T_TOP")          uvRect = sf::IntRect(sf::Vector2i(g, 0), size);
						else if (tileType == "T_TOP_RIGHT")    uvRect = sf::IntRect(sf::Vector2i(g * 2, 0), size);
						else if (tileType == "T_LEFT")         uvRect = sf::IntRect(sf::Vector2i(0, g), size);
						else if (tileType == "T_CENTER" ||
							tileType == "TERRAIN")        uvRect = sf::IntRect(sf::Vector2i(g, g), size);
						else if (tileType == "T_RIGHT")        uvRect = sf::IntRect(sf::Vector2i(g * 2, g), size);
						else if (tileType == "T_BOTTOM_LEFT")  uvRect = sf::IntRect(sf::Vector2i(0, g * 2), size);
						else if (tileType == "T_BOTTOM")       uvRect = sf::IntRect(sf::Vector2i(g, g * 2), size);
						else if (tileType == "T_BOTTOM_RIGHT") uvRect = sf::IntRect(sf::Vector2i(g * 2, g * 2), size);

						sprite->SetTextureRect(uvRect);
					}
				}

				// Par contre physiquement, le terrain à une collision plus simplifié, c'est pas mal en vrai :)

				GameObject* terrainContainer = CreateGameObject("Terrain", { xPos, yPos });
				terrainContainer->GetTransform().origin = sf::Vector2f(0.f, 0.f);
				terrainContainer->AddComponent<SquareCollider>(sf::Vector2f(width * gridSize, height * gridSize));

			}

			else if (tileType == "BRICK")
			{

				for (int i = 0; i < (int)width; i++)
					for (int j = 0; j < (int)height; j++)
					{
						GameObject* brick = CreateGameObject("Block", { xPos + i * gridSize, yPos + j * gridSize});
						brick->GetTransform().origin = sf::Vector2f(0.f, 0.f);
						brick->AddComponent<SquareCollider>(sf::Vector2f(gridSize, gridSize));
						brick->AddComponent<SpriteRenderer>("Assets/Environment/Brick.png");
						brick->AddComponent<InteractableBlockComponent>(InteractableBlockType::BRICK);
					}
			}

			else if (tileType == "BLOCK_COINS")
			{
				// On crée les blocs de pièces un par un
				for (int i = 0; i < (int)width; i++)
					for (int j = 0; j < (int)height; j++)
					{
						float finalX = xPos + (i * gridSize);
						float finalY = yPos + (j * gridSize);
						GameObject* blockCoins = CreateGameObject("Block", { finalX, finalY });
						blockCoins->GetTransform().origin = sf::Vector2f(0.f, 0.f);
						blockCoins->AddComponent<SquareCollider>(sf::Vector2f(gridSize, gridSize));
						blockCoins->AddComponent<SpriteRenderer>("Assets/Environment/LuckyBlock.png");
						blockCoins->AddComponent<InteractableBlockComponent>(InteractableBlockType::COINS);
					}
			}

			else if (tileType == "COINS")
			{
				// On crée chaque pièce individuellement pour qu'elles soient ramassables une par une
				for (int i = 0; i < (int)width; i++) {
					for (int j = 0; j < (int)height; j++) {
						// On centre la pièce dans sa tuile de gridSize
						float finalX = xPos + (i * gridSize) + gridSize * 0.5f;
						float finalY = yPos + (j * gridSize) + gridSize * 0.5f;

						GameObject* coins = CreateGameObject("Bonus", { finalX, finalY });
						coins->AddComponent<SpriteRenderer>("Assets/Environment/Coins.png");
						coins->AddComponent<SquareCollider>(sf::Vector2f(gridSize, gridSize));
						coins->AddComponent<BonusComponent>(BonusType::COINS);
					}
				}
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