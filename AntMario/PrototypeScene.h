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
#include "Oppenent.h"
#include "Bonus.h"

using json = nlohmann::json;

class PrototypeScene : public Scene
{

public:
	PrototypeScene()
	{

		std::ifstream file("Assets/Level/AntLevel_8.json");
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


		GameObject* opponent1 = CreateGameObject("opponent1", { 200, 700 });
		opponent1->GetTransform().scale = sf::Vector2f(0.85f, 0.85f);
		opponent1->GetTransform().origin = sf::Vector2f(0.5f, 1.f);
		opponent1->AddComponent<SpriteRenderer>("Assets/PlayerSprite.png");
		opponent1->AddComponent<VelocityComponent>(260.f);
		opponent1->AddComponent<SquareCollider>(sf::Vector2f(70.f, 140.f));

		GameObject* opponent2 = CreateGameObject("opponent2", { 250, 700 });
		opponent2->GetTransform().scale = sf::Vector2f(0.85f, 0.85f);
		opponent2->GetTransform().origin = sf::Vector2f(0.5f, 1.f);
		opponent2->AddComponent<SpriteRenderer>("Assets/PlayerSprite.png");
		opponent2->AddComponent<VelocityComponent>(260.f);
		opponent2->AddComponent<SquareCollider>(sf::Vector2f(70.f, 140.f));

		GameObject* opponent3 = CreateGameObject("opponent3", { 300, 700 });
		opponent3->GetTransform().scale = sf::Vector2f(0.85f, 0.85f);
		opponent3->GetTransform().origin = sf::Vector2f(0.5f, 1.f);
		opponent3->AddComponent<SpriteRenderer>("Assets/PlayerSprite.png");
		opponent3->AddComponent<VelocityComponent>(260.f);
		opponent3->AddComponent<SquareCollider>(sf::Vector2f(70.f, 140.f));

        // 2. PHASE VISUELLE ET OBJETS INTERACTIFS
        // On utilise la liste "tiles" qui contient tout ce qui a été dessiné
        for (const auto& tile : data["tiles"]) {
            std::string tileType = tile["type"];
            float xPos = tile["x"].get<float>() * gridSize;
            float yPos = tile["y"].get<float>() * gridSize;
            float width = tile["w"].get<float>();
            float height = tile["h"].get<float>();
            float g = gridSize;

            // --- CAS DU TERRAIN (Visuel uniquement ici) ---
            if (tileType.find("T_") == 0 || tileType == "TERRAIN") {
                for (int ix = 0; ix < (int)width; ix++) {
                    for (int iy = 0; iy < (int)height; iy++) {
                        float finalX = xPos + (ix * gridSize);
                        float finalY = yPos + (iy * gridSize);

                        // Création du GameObject visuel (Pas de SquareCollider ici !)
                        GameObject* visualTile = CreateGameObject("TerrainTile", { finalX, finalY });
                        visualTile->GetTransform().origin = sf::Vector2f(0.f, 0.f);

                        SpriteRenderer* sprite = visualTile->AddComponent<SpriteRenderer>("Assets/Environment/Tileset.png");

                        sf::IntRect uvRect;
                        sf::Vector2i size(g, g);

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
            }
            // --- CAS DES BRIQUES ---
            else if (tileType == "BRICK") {
                for (int i = 0; i < (int)width; i++) {
                    for (int j = 0; j < (int)height; j++) {
                        GameObject* brick = CreateGameObject("Block", { xPos + i * gridSize, yPos + j * gridSize });
                        brick->GetTransform().origin = sf::Vector2f(0.f, 0.f);
                        brick->AddComponent<SquareCollider>(sf::Vector2f(gridSize, gridSize));
                        brick->AddComponent<SpriteRenderer>("Assets/Environment/Brick.png");
                        brick->AddComponent<InteractableBlockComponent>(InteractableBlockType::BRICK);
                    }
                }
            }
            // --- CAS DES BLOCS A PIECES ---
            else if (tileType == "BLOCK_COINS") {
                for (int i = 0; i < (int)width; i++) {
                    for (int j = 0; j < (int)height; j++) {
                        GameObject* blockCoins = CreateGameObject("Block", { xPos + i * gridSize, yPos + j * gridSize });
                        blockCoins->GetTransform().origin = sf::Vector2f(0.f, 0.f);
                        blockCoins->AddComponent<SquareCollider>(sf::Vector2f(gridSize, gridSize));
                        blockCoins->AddComponent<SpriteRenderer>("Assets/Environment/LuckyBlock.png");
                        blockCoins->AddComponent<InteractableBlockComponent>(InteractableBlockType::COINS);
                    }
                }
            }
            // --- CAS DES PIECES ---
            else if (tileType == "COINS") {
                for (int i = 0; i < (int)width; i++) {
                    for (int j = 0; j < (int)height; j++) {
                        // Centrage de la pièce
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

        // 3. PHASE PHYSIQUE : COLLIDERS DU TERRAIN FUSIONNÉS
        // On crée les corps physiques uniquement pour le décor fusionné par l'éditeur
        for (const auto& col : data["colliders"]) {
            float cx = col["x"].get<float>() * gridSize;
            float cy = col["y"].get<float>() * gridSize;
            float cw = col["w"].get<float>() * gridSize;
            float ch = col["h"].get<float>() * gridSize;

            // On crée un objet invisible qui sert uniquement de collider pour le sol
            GameObject* terrainPhysic = CreateGameObject("Terrain", { cx, cy });
            terrainPhysic->GetTransform().origin = sf::Vector2f(0.f, 0.f);
            terrainPhysic->AddComponent<SquareCollider>(sf::Vector2f(cw, ch));

            // Note: Pas de SpriteRenderer ici car le visuel a été géré au dessus !
        }

		GameObject* player = CreateGameObject("Player", { 150, 700 });
		player->GetTransform().scale = sf::Vector2f(0.55f, 0.55f);
		player->GetTransform().origin = sf::Vector2f(0.5f, 1.f);
		player->AddComponent<FixedCameraComponent>(sf::Vector2f(1000.f, 666.f), 500.f, levelWidth - 500.f);
		player->AddComponent<SpriteRenderer>("Assets/Player.png");
		player->AddComponent<PlayerController>();
		player->AddComponent<VelocityComponent>(220.f);
		player->AddComponent<SquareCollider>(sf::Vector2f(50.f, 135.f));

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

		// déplacement des opponents vers la gauche seulement
		auto _opponent1 = GetGameObjectsByName("opponent1");
		if (_opponent1.size() == 0);
		else if (auto opponent1 = _opponent1[0])
		{
			VelocityComponent* vel = opponent1->GetComponent<VelocityComponent>();
			vel->SetX(-1.f); // Direction seulement vers la gauche
		}

		auto _opponent2 = GetGameObjectsByName("opponent2");
		if (_opponent2.size() == 0);
		else if (auto opponent2 = _opponent2[0])
		{
			VelocityComponent* vel = opponent2->GetComponent<VelocityComponent>();
			vel->SetX(-1.f); // Direction seulement vers la gauche
		}

		auto _opponent3 = GetGameObjectsByName("opponent3");
		if (_opponent3.size() == 0);
		else if (auto opponent3 = _opponent3[0])
		{
			static float timer = 0.f;
			static bool goingDown = true;

			timer += dt;

			if (timer >= 3.f) // Change de direction toutes les 3 secondes
			{
				goingDown = !goingDown;
				timer = 0.f;
			}
			opponent3->GetComponent <VelocityComponent>()->SetY(goingDown ? 1.f : -1.f);
		}


	}

};