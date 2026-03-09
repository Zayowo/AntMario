#include "Engine.h"

void Engine::Init()
{

	moduleManager->Init();

}

void Engine::Run()
{

	while (!isStopped)
	{
		moduleManager->Update();
		moduleManager->Render();
	}

	moduleManager->Destroy();

}

void Engine::Stop()
{

	isStopped = true;

}