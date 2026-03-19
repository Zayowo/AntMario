#pragma once
#include <Scene.h>
#include <SceneModule.h>
#include <ButtonRenderer.h>
#include <TextRenderer.h>
#include <GameObject.h>
#include "GameStateManager.h"

class VictoryScene : public Scene
{

public:
	VictoryScene()
	{

		isBreakingUpdate = true;

		GameObject* titleText = CreateGameObject("VictoryTitle", { 600, 250 });
		titleText->GetTransform().origin = sf::Vector2f(0.5f, 0.5f);
		titleText->SetIsAlwaysLoaded(true);
		titleText->AddComponent<TextRenderer>("Assets/UI/Font.ttf", "You Won!");

		GameObject* coinsText = CreateGameObject("CoinsText", { 600, 350 });
		coinsText->GetTransform().origin = sf::Vector2f(0.5f, 0.5f);
		coinsText->SetIsAlwaysLoaded(true);
		coinsText->AddComponent<TextRenderer>("Assets/UI/Font.ttf", "Coins collected: " + std::to_string(GameStateManager::coins));

		GameObject* nextLevelButton = CreateGameObject("NextLevelButton", { 600, 450 });
		nextLevelButton->GetTransform().origin = sf::Vector2f(0.5f, 0.5f);
		nextLevelButton->SetIsAlwaysLoaded(true);
		nextLevelButton->AddComponent<ButtonRenderer>("Assets/UI/UnhoveredButton.png", "Assets/UI/HoveredButton.png", "Next Level", []() {

			// TODO: Changer vers le niveau suivant
			Engine::GetModule<SceneModule>()->SetScene("LevelScene_1_1");

		});

		GameObject* backToMenuButton = CreateGameObject("BackToMenuButton", { 600, 550 });
		backToMenuButton->GetTransform().origin = sf::Vector2f(0.5f, 0.5f);
		backToMenuButton->SetIsAlwaysLoaded(true);
		backToMenuButton->AddComponent<ButtonRenderer>("Assets/UI/UnhoveredButton.png", "Assets/UI/HoveredButton.png", "Back To Menu", []() {

			Engine::GetModule<SceneModule>()->SetScene("MainMenuScene");

		});

	};

};
