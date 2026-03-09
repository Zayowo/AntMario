#pragma once
#include <vector>

class ModuleManager
{

public:
	// Envoie des différentes étapes pour les modules présents dans le module manager
	void Init();
	void Update();
	void Render();
	void Destroy();

private:
	std::vector<Module*> modules;

};