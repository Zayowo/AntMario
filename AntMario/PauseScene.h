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

		GameObject* continueButton = CreateGameObject("ContinueButton", { 600, 325 });
		continueButton->SetIsAlwaysLoaded(true);
		continueButton->AddComponent<ButtonRenderer>("Assets/UI/Continue_Unhovered.png", "Assets/UI/Continue_Hovered.png", "", []() {
			
			Engine::GetModule<SceneModule>()->PopScene();

		});

		GameObject* quitButton = CreateGameObject("QuitButton", { 600, 475 });
		quitButton->SetIsAlwaysLoaded(true);
		quitButton->AddComponent<ButtonRenderer>("Assets/UI/MainMenu_Unhovered.png", "Assets/UI/MainMenu_Hovered.png", "", []() {

			Engine::GetModule<SceneModule>()->SetScene("MainMenuScene");

		});

	};

};