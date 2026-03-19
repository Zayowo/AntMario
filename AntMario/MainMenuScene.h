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

		GameObject* playButton = CreateGameObject("Button", { 600, 300 });
		playButton->AddComponent<ButtonRenderer>("Assets/UI/UnhoveredButton.png", "Assets/UI/HoveredButton.png", "Play", []() {

			Engine::GetModule<SceneModule>()->SetScene("LevelScene_1_1");

		});

		GameObject* editorButton = CreateGameObject("Button", { 600, 400 });
		editorButton->AddComponent<ButtonRenderer>("Assets/UI/UnhoveredButton.png", "Assets/UI/HoveredButton.png", "Settings", []() {

			// À ajouter!

		});

		GameObject* quitButton = CreateGameObject("Button", { 600, 500 });
		quitButton->AddComponent<ButtonRenderer>("Assets/UI/UnhoveredButton.png", "Assets/UI/HoveredButton.png", "Quit", []() {

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