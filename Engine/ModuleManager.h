#pragma once
#include <vector>
#include "Module.h"

class ModuleManager
{

public:
	// Envoie des différentes étapes pour les modules présents dans le module manager
	void Init();
	void Update();
	void Render();
	void Destroy();

	// Enregistre un module de type
	template<typename ModuleType>
	Module* RegisterModule();

private:
	std::vector<Module*> modules;

};

#include "ModuleManager.inl"