#pragma once
#include <Engine.h>
#include <SceneModule.h>
#include <Scene.h>
#include <ButtonRenderer.h>

class MainMenuScene : public Scene
{

public:
	MainMenuScene()
	{

		GameObject* playButton = CreateGameObject("Button", { 600, 350 });
		playButton->AddComponent<ButtonRenderer>("Assets/UI/UnhoveredButton.png", "Assets/UI/HoveredButton.png", "Play", []() {

			Engine::GetModule<SceneModule>()->SetScene("PrototypeScene");

		});

		GameObject* quitButton = CreateGameObject("Button", { 600, 450 });
		quitButton->AddComponent<ButtonRenderer>("Assets/UI/UnhoveredButton.png", "Assets/UI/HoveredButton.png", "Quit", []() {

			Engine::GetInstance()->Stop();

		});

	};

};