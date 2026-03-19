#pragma once
#include <Scene.h>
#include <SceneModule.h>
#include <ButtonRenderer.h>
#include <TextRenderer.h>
#include <GameObject.h>

class GameOverScene : public Scene
{

public:
	GameOverScene()
	{

		isBreakingUpdate = true;

		GameObject* titleText = CreateGameObject("GameOverTitle", { 600, 250 });
		titleText->GetTransform().origin = sf::Vector2f(0.5f, 0.5f);
		titleText->SetIsAlwaysLoaded(true);
		titleText->AddComponent<TextRenderer>("Assets/UI/Font.ttf", "Game Over.");

		GameObject* tryAgainButton = CreateGameObject("TryAgainButton", { 600, 400 });
		tryAgainButton->GetTransform().origin = sf::Vector2f(0.5f, 0.5f);
		tryAgainButton->SetIsAlwaysLoaded(true);
		tryAgainButton->AddComponent<ButtonRenderer>("Assets/UI/UnhoveredButton.png", "Assets/UI/HoveredButton.png", "Try Again", []() {

			Engine::GetModule<SceneModule>()->SetScene("LevelScene_1_1");

		});

		GameObject* backToMenuButton = CreateGameObject("BackToMenuButton", { 600, 500 });
		backToMenuButton->GetTransform().origin = sf::Vector2f(0.5f, 0.5f);
		backToMenuButton->SetIsAlwaysLoaded(true);
		backToMenuButton->AddComponent<ButtonRenderer>("Assets/UI/UnhoveredButton.png", "Assets/UI/HoveredButton.png", "Back To Menu", []() {

			Engine::GetModule<SceneModule>()->SetScene("MainMenuScene");

		});

	};

};
