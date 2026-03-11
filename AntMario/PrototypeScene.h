#pragma once
#include <Scene.h>
#include <SpriteRenderer.h>
#include <VelocityComponent.h>
#include <SquareCollider.h>
#include <ButtonRenderer.h>
#include "BackgroundElement.h"
#include "FixedCameraComponent.h"
#include "PlayerController.h"

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
		// player->AddComponent<FixedCameraComponent>(sf::Vector2f(1200, 900));
		player->AddComponent<SpriteRenderer>("Assets/PlayerSprite.png");
		player->AddComponent<VelocityComponent>(260.f);
		player->AddComponent<PlayerController>();
		player->AddComponent<SquareCollider>(sf::Vector2f(40.f, 60.f));

	};

};