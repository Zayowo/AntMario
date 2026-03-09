#include <iostream>
#include "Engine.h"

Engine* Engine::instance = nullptr;
ModuleManager* Engine::moduleManager = nullptr;

void Engine::Init()
{

	if (!moduleManager)
		moduleManager = new ModuleManager();

	moduleManager->Init();
	std::cout << "Engine is initialized!" << std::endl;

}

void Engine::Run()
{

	while (!isStopped)
	{
		moduleManager->Update();
		moduleManager->Render();
	}

	moduleManager->Destroy();
	std::cout << "Engine is stopped!" << std::endl;

}

void Engine::Stop()
{

	isStopped = true;

}