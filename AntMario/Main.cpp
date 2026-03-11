#include <Engine.h>
#include <InputModule.h>
#include <SceneModule.h>
#include "MainMenuScene.h"
#include "PrototypeScene.h"

int main()
{

	Engine* engine = Engine::GetInstance();
	engine->Init();

	// Ajout des inputs
	InputModule* inputModule = Engine::GetModule<InputModule>();
	inputModule->RegisterInput(sf::Mouse::Button::Left);
	inputModule->RegisterInput(sf::Keyboard::Key::Q);
	inputModule->RegisterInput(sf::Keyboard::Key::D);

	// Ajout des scènes
	SceneModule* sceneModule = Engine::GetModule<SceneModule>();
	sceneModule->RegisterScene<MainMenuScene>("MainMenuScene");
	sceneModule->RegisterScene<PrototypeScene>("PrototypeScene");
	sceneModule->PushScene("MainMenuScene");

	engine->Run();

}