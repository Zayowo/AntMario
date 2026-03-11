#pragma once
#include <Scene.h>
#include <SpriteRenderer.h>
#include <VelocityComponent.h>
#include <SquareCollider.h>
#include <ButtonRenderer.h>
#include "PlayerController.h"
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
		// player
		GameObject* player = CreateGameObject("Player", { 150, 600 });
		player->AddComponent<SpriteRenderer>("Assets/PlayerSprite.png");
		player->AddComponent<VelocityComponent>(180.f);
		player->AddComponent<PlayerController>();
		player->AddComponent<SquareCollider>(sf::Vector2f(40.f, 60.f));

		FSMComponent<PlayerContext>* fsmPlayer = player->AddComponent<FSMComponent<PlayerContext>>();
		PlayerContext& ctxPlayer = fsmPlayer->GetContext();
		ctxPlayer.player = player;

		LittleState* littleState = fsmPlayer->CreateState<LittleState>();
		BigState* bigState = fsmPlayer->CreateState<BigState>();
		bigState->AddTransition(Condition::collisionWithEnemy, littleState);
		FireState* fireState = fsmPlayer->CreateState<FireState>();
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