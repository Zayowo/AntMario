#pragma once
#include <Scene.h>
#include <SceneModule.h>
#include <ButtonRenderer.h>
#include <TextRenderer.h>
#include <GameObject.h>
#include <sstream>
#include <iomanip>
#include "GameStateManager.h"

class LifeLostScene : public Scene
{

public:
	LifeLostScene()
	{

		isBreakingUpdate = true;

		GameObject* titleText = CreateGameObject("LifeLostTitle", { 600, 250 });
		titleText->SetIsAlwaysLoaded(true);
		titleText->AddComponent<TextRenderer>("Assets/UI/Font.ttf", "Oof...");

		GameObject* livesText = CreateGameObject("LivesText", { 600, 350 });
		livesText->SetIsAlwaysLoaded(true);
		livesText->AddComponent<TextRenderer>("Assets/UI/Font.ttf", "You have " + std::to_string(GameStateManager::GetLives()) + " lives remaining...");

		GameObject* continueButton = CreateGameObject("ContinueButton", { 600, 450 });
		continueButton->SetIsAlwaysLoaded(true);
		continueButton->AddComponent<ButtonRenderer>("Assets/UI/UnhoveredButton.png", "Assets/UI/HoveredButton.png", "Continue", []() {

			Engine::GetModule<SceneModule>()->SetScene("PrototypeScene");

		});

	};

};
