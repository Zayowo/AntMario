#pragma once
#include <Scene.h>
#include <Engine.h>
#include <SceneModule.h>
#include <InputModule.h>
#include <SpriteRenderer.h>

class MapEditorScene : public Scene
{

public:
	MapEditorScene()
	{

		GameObject* sky = CreateGameObject("Sky", { 600, 400 });
		sky->GetTransform().scale = sf::Vector2f(200.f, 2.f);
		sky->AddComponent<SpriteRenderer>("Assets/Environment/SkyNormal.png");

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