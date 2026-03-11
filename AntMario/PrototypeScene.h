#pragma once
#include <Scene.h>
#include <SpriteRenderer.h>
#include <VelocityComponent.h>
#include <SquareCollider.h>
#include <ButtonRenderer.h>
#include "PlayerController.h"
#include "Bonus.h"


class PrototypeScene : public Scene
{

public:
	PrototypeScene()
	{

		GameObject* player = CreateGameObject("Player", { 150, 600 });
		player->AddComponent<SpriteRenderer>("Assets/PlayerSprite.png");
		player->AddComponent<VelocityComponent>(180.f);
		player->AddComponent<PlayerController>();
		player->AddComponent<SquareCollider>(sf::Vector2f(40.f, 60.f));


		// De maniere temporaire pour vérifier si les bonus s'affichent bien
		GameObject* bonus = CreateGameObject("Coins", { 180, 600 });
		bonus->AddComponent<Bonus>(BonusType::Coins);

		GameObject* bonus1 = CreateGameObject("Bonus1", { 240, 600 });
		bonus1->AddComponent<Bonus>(BonusType::Bonus1);

		GameObject* bonus2 = CreateGameObject("Bonus2", { 310, 600 });
		bonus2->AddComponent<Bonus>(BonusType::Bonus2);

		GameObject* bonus3 = CreateGameObject("Bonus3", { 400, 600 });
		bonus3->AddComponent<Bonus>(BonusType::Bonus3);

	};

};