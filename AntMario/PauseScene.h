#pragma once
#include <Scene.h>
#include <SceneModule.h>
#include <ButtonRenderer.h>

class PauseScene : public Scene
{

public:
	PauseScene()
	{

		isBreakingUpdate = true;

		GameObject* continueButton = CreateGameObject("ContinueButton", { 600, 350 });
		continueButton->SetIsAlwaysLoaded(true);
		continueButton->AddComponent<ButtonRenderer>("Assets/UI/UnhoveredButton.png", "Assets/UI/HoveredButton.png", "Continue", []() {
			
			Engine::GetModule<SceneModule>()->PopScene();

		});

		GameObject* quitButton = CreateGameObject("QuitButton", { 600, 450 });
		quitButton->SetIsAlwaysLoaded(true);
		quitButton->AddComponent<ButtonRenderer>("Assets/UI/UnhoveredButton.png", "Assets/UI/HoveredButton.png", "Quit", []() {

			Engine::GetModule<SceneModule>()->SetScene("MainMenuScene");

		});

	};

};