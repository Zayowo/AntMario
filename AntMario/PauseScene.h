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
		continueButton->AddComponent<ButtonRenderer>("Assets/UI/UnhoveredButton.png", "Assets/UI/HoveredButton.png", "Continue", []() {
			
			Engine::GetModule<SceneModule>()->PopScene();

		});

		GameObject* quitButton = CreateGameObject("QuitButton", { 600, 450 });
		quitButton->AddComponent<ButtonRenderer>("Assets/UI/UnhoveredButton.png", "Assets/UI/HoveredButton.png", "Quit", []() {

			Engine::GetModule<SceneModule>()->SetScene("MainMenuScene");

		});

	};

	void Update(float dt)
	{

		sf::RenderWindow* window = Engine::GetModule<WindowModule>()->GetRenderWindow();
		sf::View currentView = window->getView();
		window->setView(window->getDefaultView());
		Scene::Update(dt);
		window->setView(currentView);

	}

	void Render(sf::RenderWindow* window)
	{

		sf::View currentView = window->getView();
		window->setView(window->getDefaultView());
		Scene::Render(window);
		window->setView(currentView);

	}

};