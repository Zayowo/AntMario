#pragma once
#include <Scene.h>
#include <Engine.h>
#include <SceneModule.h>
#include <InputModule.h>
#include <SpriteRenderer.h>
#include "BackgroundElement.h"

class MapEditorScene : public Scene
{

public:
	MapEditorScene()
	{

		GameObject* sky = CreateGameObject("Sky", { 600, 400 });
		sky->GetTransform().scale = sf::Vector2f(3.f, 3.f);
		sky->AddComponent<BackgroundElement>("Assets/Environment/Background.png", 1.f, sf::Vector2f(-600.f, 0.f));

	};

	void Update(float dt) override
	{

		InputModule* inputModule = Engine::GetModule<InputModule>();
		SceneModule* sceneModule = Engine::GetModule<SceneModule>();

		if (inputModule->Is(sf::Keyboard::Key::Escape, InputState::PRESSED))
			sceneModule->SetScene("MainMenuScene");

		Scene::Update(dt);

	}

};