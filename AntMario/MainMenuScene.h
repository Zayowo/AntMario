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
		playButton->AddComponent<ButtonRenderer>("Assets/UI/UnhoveredButton.png", "Assets/UI/HoveredButton.png", "Play", []() {

			Engine::GetModule<SceneModule>()->SetScene("PrototypeScene");

		});

		GameObject* editorButton = CreateGameObject("Button", { 600, 400 });
		editorButton->AddComponent<ButtonRenderer>("Assets/UI/UnhoveredButton.png", "Assets/UI/HoveredButton.png", "I don't know", []() {

			Engine::GetModule<SceneModule>()->SetScene("MapEditorScene");

		});

		GameObject* quitButton = CreateGameObject("Button", { 600, 500 });
		quitButton->AddComponent<ButtonRenderer>("Assets/UI/UnhoveredButton.png", "Assets/UI/HoveredButton.png", "Quit", []() {

			Engine::GetInstance()->Stop();

		});

	};


};