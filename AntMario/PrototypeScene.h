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

		FSMComponent<PlayerContext>* fsmPlayer = player->AddComponent<FSMComponent<PlayerContext>>();
		PlayerContext& ctxPlayer = fsmPlayer->GetContext();
		ctxPlayer.player = player;

		LittleState* littleState = fsmPlayer->CreateState<LittleState>();
		
		fsmPlayer->Init(littleState);


		

	};

};