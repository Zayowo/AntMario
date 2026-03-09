#pragma once
#include "Scene.h"
#include "SpriteRenderer.h"

class PrototypeScene : public Scene
{

public:
	PrototypeScene()
	{

		GameObject* player = CreateGameObject("Player", { 640, 360 });
		player->AddComponent<SpriteRenderer>("Assets/PlayerSprite.png");

	};

};