#include "ModuleManager.h"
#include "ResourceModule.h"
#include "WindowModule.h"
#include "InputModule.h"
#include "TimeModule.h"
#include "SceneModule.h"

void ModuleManager::Init() {

	RegisterModule<ResourceModule>();
	RegisterModule<InputModule>();
	RegisterModule<TimeModule>();
	RegisterModule<SceneModule>();
	RegisterModule<WindowModule>();

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