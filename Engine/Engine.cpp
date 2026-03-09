#include <iostream>
#include "Engine.h"

Engine* Engine::instance = nullptr;

void Engine::Init()
{

	moduleManager->Init();
	std::cout << "Engine has been initialized!" << std::endl;

}

void Engine::Run()
{

	while (!isStopped)
	{
		moduleManager->Update();
		moduleManager->Render();
	}

	moduleManager->Destroy();
	std::cout << "Engine has been stopped!" << std::endl;

}

void Engine::Stop()
{

	isStopped = true;

}