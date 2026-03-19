#pragma once
#include <Engine.h>
#include <SceneModule.h>
#include <Scene.h>
#include <ButtonRenderer.h>
#include <SpriteRenderer.h>
#include "GameStateManager.h"
#include "BackgroundElement.h"

class MainMenuScene : public Scene
{

public:
	MainMenuScene()
	{

		// Réinitialiser l'état du jeu quand on revient au menu principal
		GameStateManager::ResetGame();

		GameObject* background = CreateGameObject("Menu", { 600, 400 });
		background->AddComponent<SpriteRenderer>("Assets/MainMenu.png");
		background->GetTransform().scale = sf::Vector2f(1.f, 1.f);

		GameObject* playButton = CreateGameObject("Button", { 600, 250 });
		playButton->AddComponent<ButtonRenderer>("Assets/UI/StartGame_Unhovered.png", "Assets/UI/StartGame_Hovered.png", "", []() {

			Engine::GetModule<SceneModule>()->SetScene("LevelScene_1_1");

		});

		GameObject* settingsButton = CreateGameObject("Button", { 600, 400 });
		settingsButton->AddComponent<ButtonRenderer>("Assets/UI/Settings_Unhovered.png", "Assets/UI/Settings_Hovered.png", "", []() {

			// Euh, bon! :)

		});

		GameObject* quitButton = CreateGameObject("Button", { 600, 550 });
		quitButton->AddComponent<ButtonRenderer>("Assets/UI/QuitGame_Unhovered.png", "Assets/UI/QuitGame_Hovered.png", "", []() {

			Engine::GetInstance()->Stop();

		});

	};

	void Update(float dt)
	{

		sf::RenderWindow* window = Engine::GetModule<WindowModule>()->GetRenderWindow();
		sf::View view = window->getView();
		window->setView(window->getDefaultView());

		Scene::Update(dt);

		window->setView(view);

	}

	void Render(sf::RenderWindow* window)
	{

		sf::View view = window->getView();
		window->setView(window->getDefaultView());

		Scene::Render(window);

		window->setView(view);

	}


};