#include <Engine.h>
#include <InputModule.h>
#include <SceneModule.h>
#include <ResourceModule.h>
#include "MainMenuScene.h"
#include "PrototypeScene.h"
#include "PauseScene.h"

int main()
{

	Engine* engine = Engine::GetInstance();
	engine->Init();

	// Ajout des inputs
	InputModule* inputModule = Engine::GetModule<InputModule>();
	inputModule->RegisterInput(sf::Mouse::Button::Left);
	inputModule->RegisterInput(sf::Keyboard::Key::Escape);
	inputModule->RegisterInput(sf::Keyboard::Key::Q);
	inputModule->RegisterInput(sf::Keyboard::Key::D);
	inputModule->RegisterInput(sf::Keyboard::Key::Space);
	inputModule->RegisterInput(sf::Keyboard::Key::LShift);
	inputModule->RegisterInput(sf::Keyboard::Key::PageUp);
	inputModule->RegisterInput(sf::Keyboard::Key::PageDown);

	// Ajout des scènes
	SceneModule* sceneModule = Engine::GetModule<SceneModule>();
	sceneModule->RegisterScene<MainMenuScene>("MainMenuScene");
	sceneModule->RegisterScene<PrototypeScene>("PrototypeScene");
	sceneModule->RegisterScene<PauseScene>("PauseScene");
	sceneModule->PushScene("MainMenuScene");

	// Load les sons
	ResourceModule* resourceModule = Engine::GetModule<ResourceModule>();
	resourceModule->GetSound("Assets/Sounds/Brick.wav");
	resourceModule->GetSound("Assets/Sounds/Coin.wav");
	resourceModule->GetSound("Assets/Sounds/Jump.wav");


	engine->Run();

}