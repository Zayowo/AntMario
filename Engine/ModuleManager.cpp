#include "ModuleManager.h"
#include "InputModule.h"
#include "TimeModule.h"
#include "SceneModule.h"

void ModuleManager::Init() {

	RegisterModule<InputModule>();
	RegisterModule<TimeModule>();
	RegisterModule<SceneModule>();

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