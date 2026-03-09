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

	// Crée un module de type correspondant
	template<typename ModuleType>
	Module* CreateModule();

private:
	std::vector<Module*> modules;

};

#include "ModuleManager.inl"