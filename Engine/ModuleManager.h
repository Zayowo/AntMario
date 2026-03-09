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

	// Récupère un module de type
	template<typename ModuleType>
	Module* GetModule()
	{

		for (Module* module : modules)
			if (ModuleType* moduleType = dynamic_cast<ModuleType*>(module))
				return moduleType;

		return nullptr;

	}

private:
	std::vector<Module*> modules;

};

#include "ModuleManager.inl"