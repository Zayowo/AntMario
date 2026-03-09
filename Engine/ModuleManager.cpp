#include "ModuleManager.h"

void ModuleManager::Init() {

	

	for (Module* module : modules)
		module->Init();

}

void ModuleManager::Update() {

	for (Module* module : modules)
		module->Update();

}

void ModuleManager::Render() {

	for (Module* module : modules)
		module->Render();

}

void ModuleManager::Destroy() {

	for (Module* module : modules)
		module->Destroy();

}