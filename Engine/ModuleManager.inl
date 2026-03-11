#pragma once

template<typename ModuleType>
Module* ModuleManager::RegisterModule()
{

	ModuleType* module = new ModuleType();
	modules.emplace_back(module);
	return module;

}