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

		GameObject* playButton = CreateGameObject("Button", { 600, 300 });
		playButton->SetIsAlwaysLoaded(true);
		playButton->AddComponent<ButtonRenderer>("Assets/UI/UnhoveredButton.png", "Assets/UI/HoveredButton.png", "Play", []() {

			Engine::GetModule<SceneModule>()->SetScene("PrototypeScene");

		});

		GameObject* editorButton = CreateGameObject("Button", { 600, 400 });
		editorButton->SetIsAlwaysLoaded(true);
		editorButton->AddComponent<ButtonRenderer>("Assets/UI/UnhoveredButton.png", "Assets/UI/HoveredButton.png", "Settings", []() {

			// À ajouter!

		});

		GameObject* quitButton = CreateGameObject("Button", { 600, 500 });
		quitButton->SetIsAlwaysLoaded(true);
		quitButton->AddComponent<ButtonRenderer>("Assets/UI/UnhoveredButton.png", "Assets/UI/HoveredButton.png", "Quit", []() {

			Engine::GetInstance()->Stop();

		});

	};


};