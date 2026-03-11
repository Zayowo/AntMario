#pragma once
#include <Scene.h>
#include <SpriteRenderer.h>
#include <VelocityComponent.h>
#include <SquareCollider.h>
#include <ButtonRenderer.h>
#include "BackgroundElement.h"
#include "FixedCameraComponent.h"
#include "PlayerController.h"
#include "Bonus.h"


class PrototypeScene : public Scene
{

public:
	PrototypeScene()
	{

		GameObject* sky = CreateGameObject("Sky", { 600, 400 });
		sky->GetTransform().scale = sf::Vector2f(200.f, 2.f);
		sky->AddComponent<SpriteRenderer>("Assets/Environment/SkyNormal.png");
		
		for (int i = 0; i < 2; i++)
		{

			GameObject* cloud = CreateGameObject("Cloud", { 0, 300 });
			cloud->AddComponent<BackgroundElement>("Assets/Environment/Cloud.png", 0.75f, sf::Vector2f(i * 500, i * 50.f));

		}

		GameObject* player = CreateGameObject("Player", { 150, 700 });
		player->GetTransform().scale = sf::Vector2f(1.f, 0.75f);
		player->GetTransform().origin = sf::Vector2f(0.5f, 1.f);
		player->AddComponent<SpriteRenderer>("Assets/PlayerSprite.png");
		player->AddComponent<PlayerController>();
		player->AddComponent<VelocityComponent>(260.f);
		player->AddComponent<SquareCollider>(sf::Vector2f(40.f, 60.f));

		// De maniere temporaire pour vérifier si les bonus s'affichent bien
		GameObject* bonus = CreateGameObject("Coins", { 180, 600 });
		bonus->AddComponent<Bonus>(BonusType::Coins);
		bonus->AddComponent<SquareCollider>(sf::Vector2f(40.f, 40.f));

		GameObject* bonus1 = CreateGameObject("Bonus1", { 240, 600 });
		bonus1->AddComponent<Bonus>(BonusType::Bonus1);
		bonus1->AddComponent<SquareCollider>(sf::Vector2f(40.f, 40.f));

		GameObject* bonus2 = CreateGameObject("Bonus2", { 310, 600 });
		bonus2->AddComponent<Bonus>(BonusType::Bonus2);
		bonus2->AddComponent<SquareCollider>(sf::Vector2f(40.f, 40.f));

		GameObject* bonus3 = CreateGameObject("Bonus3", { 400, 600 });
		bonus3->AddComponent<Bonus>(BonusType::Bonus3);
		bonus3->AddComponent<SquareCollider>(sf::Vector2f(40.f, 40.f));

		for (int i = 0; i < 50; i++)
		{

			GameObject* collider = CreateGameObject("Collider", { 0 + (float)(i * 64), 800 });
			collider->GetTransform().origin = sf::Vector2f(0.f, 1.f);
			collider->AddComponent<SquareCollider>(sf::Vector2f(64.f, 64.f));

		}

	};

};