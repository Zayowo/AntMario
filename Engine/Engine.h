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
	static Engine* GetInstance()
	{

		if (!instance)
			instance = new Engine();

		return instance;

	}

	// Récupère un module présent dans le moteur
	template<typename ModuleType>
	static ModuleType* GetModule()
	{

		return moduleManager->GetModule<ModuleType>();

	}

private:
	static Engine* instance;
	static ModuleManager* moduleManager;
	bool isStopped = false;

};