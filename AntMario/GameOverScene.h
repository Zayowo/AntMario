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

		// Réinitialiser l'état du jeu quand on arrive au Game Over
		GameStateManager::ResetGame();

		GameObject* titleText = CreateGameObject("GameOverTitle", { 600, 250 });
		titleText->GetTransform().origin = sf::Vector2f(0.5f, 0.5f);
		titleText->SetIsAlwaysLoaded(true);
		titleText->AddComponent<TextRenderer>("Assets/UI/Font.ttf", "Game Over.");

		GameObject* tryAgainButton = CreateGameObject("TryAgainButton", { 600, 400 });
		tryAgainButton->GetTransform().origin = sf::Vector2f(0.5f, 0.5f);
		tryAgainButton->SetIsAlwaysLoaded(true);
		tryAgainButton->AddComponent<ButtonRenderer>("Assets/UI/Restart_Unhovered.png", "Assets/UI/Restart_Hovered.png", "", []() {

			Engine::GetModule<SceneModule>()->SetScene("LevelScene_1_1");

		});

		GameObject* backToMenuButton = CreateGameObject("BackToMenuButton", { 600, 550 });
		backToMenuButton->GetTransform().origin = sf::Vector2f(0.5f, 0.5f);
		backToMenuButton->SetIsAlwaysLoaded(true);
		backToMenuButton->AddComponent<ButtonRenderer>("Assets/UI/MainMenu_Unhovered.png", "Assets/UI/MainMenu_Hovered.png", "", []() {

			Engine::GetModule<SceneModule>()->SetScene("MainMenuScene");

		});

	};

};
