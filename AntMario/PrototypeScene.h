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
#include "FSMComponent.h"
#include "PlayerContext.h"
#include "LittleState.h"
#include "GoombaComponent.h"
#include "BigState.h"
#include "FireState.h"
#include "Condition.h"


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
		
		// player
		GameObject* player = CreateGameObject("Player", { 150, 700 });
		player->AddComponent<PlayerController>();
		player->AddComponent<VelocityComponent>(260.f);
		player->AddComponent<SpriteRenderer>("Assets/PlayerSprite.png");
		player->AddComponent<SquareCollider>(sf::Vector2f(40.f, 60.f));
		player->GetTransform().scale = sf::Vector2f(1.f, 0.75f);
		player->GetTransform().origin = sf::Vector2f(0.5f, 1.f);


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

		FSMComponent<PlayerContext>* fsmPlayer = player->AddComponent<FSMComponent<PlayerContext>>();
		PlayerContext& ctxPlayer = fsmPlayer->GetContext();
		ctxPlayer.player = player;

		//add bonus in context

		//all state
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
		GameObject* goomba = CreateGameObject("Enemy", { 300, 600 });
		goomba->AddComponent<SpriteRenderer>("Assets/PlayerSprite.png");
		goomba->AddComponent<VelocityComponent>(90.f);
		goomba->AddComponent<GoombaComponent>();
		goomba->AddComponent<SquareCollider>(sf::Vector2f(40.f, 60.f));
		ctxPlayer.enemies.emplace_back(goomba);
	};

};