#pragma once
#include <Scene.h>
#include <TimeModule.h>
#include <SpriteRenderer.h>
#include <TilemapRenderer.h>
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
#include "Oppenent.h"
#include "Bonus.h"
#include "GoombaComponent.h"
#include "PiranhaComponent.h"

using json = nlohmann::json;

class PrototypeScene : public Scene
{

public:
	PrototypeScene()
	{

		std::ifstream file("Assets/Level/AntLevel_10.json");
		json data;
		file >> data;

		float levelWidth = data["metadata"]["width"];
		float gridSize = data["metadata"]["tileSize"];

		GameObject* sky = CreateGameObject("Sky", { 600, 600 });
		sky->GetTransform().scale = sf::Vector2f(2.4f, 2.f);
		sky->SetIsAlwaysLoaded(true);
		sky->AddComponent<BackgroundElement>("Assets/Environment/Background.png", 1.f, sf::Vector2f(-900.f, 0.f));

		GameObject* sky1 = CreateGameObject("Sky", { 600, 600 });
		sky1->GetTransform().scale = sf::Vector2f(2.4f, 2.f);
		sky1->SetIsAlwaysLoaded(true);
		sky1->AddComponent<BackgroundElement>("Assets/Environment/Background.png", 1.f, sf::Vector2f(-300.f, 0.f));

		GameObject* tilemapObject = CreateGameObject("LevelTilemap", { 0.f, 0.f });
		tilemapObject->GetTransform().origin = { 0.f, 0.f };
		tilemapObject->SetIsAlwaysLoaded(true);
		TilemapRenderer* tilemap = tilemapObject->AddComponent<TilemapRenderer>("Assets/Environment/Tileset.png", sf::Vector2u(gridSize, gridSize), 500, 50);

		for (const auto& tile : data["tiles"]) {
			std::string tileType = tile["type"];
			float xPos = tile["x"].get<float>() * gridSize;
			float yPos = tile["y"].get<float>() * gridSize;
			float width = tile["w"].get<float>();
			float height = tile["h"].get<float>();
			int g = (int)gridSize;

			if (tileType.find("T_") == 0 || tileType == "TERRAIN") {

				sf::Vector2i uvCoords;
				if (tileType == "T_TOP_LEFT")           uvCoords = { 0, 0 };
				else if (tileType == "T_TOP")           uvCoords = { g, 0 };
				else if (tileType == "T_TOP_RIGHT")     uvCoords = { g * 2, 0 };
				else if (tileType == "T_LEFT")          uvCoords = { 0, g };
				else if (tileType == "T_CENTER" ||
					tileType == "TERRAIN")         uvCoords = { g, g };
				else if (tileType == "T_RIGHT")         uvCoords = { g * 2, g };
				else if (tileType == "T_BOTTOM_LEFT")   uvCoords = { 0, g * 2 };
				else if (tileType == "T_BOTTOM")        uvCoords = { g, g * 2 };
				else if (tileType == "T_BOTTOM_RIGHT")  uvCoords = { g * 2, g * 2 };

				for (int ix = 0; ix < (int)width; ix++) {
					for (int iy = 0; iy < (int)height; iy++) {
						int gridX = (int)tile["x"].get<float>() + ix;
						int gridY = (int)tile["y"].get<float>() + iy;
						tilemap->SetTile(gridX, gridY, uvCoords);
					}
				}
			}

			else if (tileType == "BRICK") {
				for (int i = 0; i < (int)width; i++) {
					for (int j = 0; j < (int)height; j++) {
						GameObject* brick = CreateGameObject("Block", { xPos + i * gridSize, yPos + j * gridSize });
						brick->GetTransform().origin = { 0.f, 0.f };
						brick->AddComponent<SquareCollider>(sf::Vector2f(gridSize, gridSize));
						brick->AddComponent<SpriteRenderer>("Assets/Environment/Brick.png");
						brick->AddComponent<InteractableBlockComponent>(InteractableBlockType::BRICK);
					}
				}
			}
			else if (tileType == "BLOCK_COINS") {
				for (int i = 0; i < (int)width; i++) {
					for (int j = 0; j < (int)height; j++) {
						GameObject* block = CreateGameObject("Block", { xPos + i * gridSize, yPos + j * gridSize });
						block->GetTransform().origin = { 0.f, 0.f };
						block->AddComponent<SquareCollider>(sf::Vector2f(gridSize, gridSize));
						block->AddComponent<SpriteRenderer>("Assets/Environment/LuckyBlock.png");
						block->AddComponent<InteractableBlockComponent>(InteractableBlockType::COINS);
					}
				}
			}
			else if (tileType == "REVERSE_WALK") {
				for (int i = 0; i < (int)width; i++) {
					for (int j = 0; j < (int)height; j++) {
						GameObject* block = CreateGameObject("ReverseWalk", { xPos + i * gridSize, yPos + j * gridSize });
						block->GetTransform().origin = { 0.f, 0.f };
						block->AddComponent<SquareCollider>(sf::Vector2f(gridSize, gridSize));
						block->AddComponent<SpriteRenderer>("Assets/Environment/ReverseWalk.png");
					}
				}
			}

			else if (tileType == "COINS") {
				for (int i = 0; i < (int)width; i++) {
					for (int j = 0; j < (int)height; j++) {
						float finalX = xPos + (i * gridSize) + gridSize * 0.5f;
						float finalY = yPos + (j * gridSize) + gridSize * 0.5f;

						GameObject* coins = CreateGameObject("Bonus", { finalX, finalY });
						coins->AddComponent<SpriteRenderer>("Assets/Environment/Coins.png");
						coins->AddComponent<SquareCollider>(sf::Vector2f(gridSize, gridSize));
						coins->AddComponent<BonusComponent>(BonusType::COINS);
					}
				}
			}
			else if (tileType == "GOOMBA") {
				for (int i = 0; i < (int)width; i++) {
					for (int j = 0; j < (int)height; j++) {
						float finalX = xPos + (i * gridSize) + gridSize * 0.5f;
						float finalY = yPos + (j * gridSize) + gridSize * 0.5f;

						GameObject* goomba = CreateGameObject("Goomba", { finalX, finalY });
						goomba->GetTransform().origin = sf::Vector2f(0.5f, 1.f);
						goomba->AddComponent<GoombaComponent>();
						goomba->AddComponent<SpriteRenderer>("Assets/Goomba.png");
						goomba->AddComponent<VelocityComponent>(90.f);
						goomba->AddComponent<SquareCollider>(sf::Vector2f(40.f, 40.f));
					}
				}
			}
		}

		// 3. PHASE PHYSIQUE
		for (const auto& col : data["colliders"]) {
			float cx = col["x"].get<float>() * gridSize;
			float cy = col["y"].get<float>() * gridSize;
			float cw = col["w"].get<float>() * gridSize;
			float ch = col["h"].get<float>() * gridSize;

			GameObject* terrainPhysic = CreateGameObject("Terrain", { cx, cy });
			terrainPhysic->GetTransform().origin = { 0.f, 0.f };
			terrainPhysic->AddComponent<SquareCollider>(sf::Vector2f(cw, ch));
		}

		GameObject* player = CreateGameObject("Player", { 500, 700 });
		player->GetTransform().scale = sf::Vector2f(0.55f, 0.55f);
		player->GetTransform().origin = sf::Vector2f(0.5f, 1.f);
		player->AddComponent<FixedCameraComponent>(sf::Vector2f(1000.f, 666.f), 500.f, levelWidth - 500.f);
		player->AddComponent<SpriteRenderer>("Assets/Player.png");
		player->AddComponent<PlayerController>();
		player->AddComponent<VelocityComponent>(200.f);
		player->AddComponent<SquareCollider>(sf::Vector2f(50.f, 135.f));

		GameObject* gameController = CreateGameObject("GameController", { 0.f, 0.f });
		gameController->AddComponent<GameController>();
		gameController->SetIsAlwaysLoaded(true);
		
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