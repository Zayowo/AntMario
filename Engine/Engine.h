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

private:
	static Engine* instance;
	ModuleManager* moduleManager = new ModuleManager();
	bool isStopped;

};