#pragma once
#include "ModuleManager.h"

class Engine
{

public:
	// Initialise le moteur
	void Init();

	// Lance la boucle principal du moteur
	void Run();

	// Demande l'arrêt du moteur
	void Stop();

	// Récupère l'instance du moteur
	Engine* GetInstance()
	{

		if (!instance)
			instance = new Engine();

		return instance;

	}

	// Récupère l'instance du module manager du moteur
	ModuleManager* GetModuleManager()
	{

		if (!moduleManager)
			moduleManager = new ModuleManager();

		return moduleManager;

	}

private:
	static Engine* instance;
	ModuleManager* moduleManager;
	bool isStopped;

};