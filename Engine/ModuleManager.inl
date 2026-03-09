
template<typename ModuleType>
Module* ModuleManager::RegisterModule()
{

	ModuleType* module = new ModuleType();
	modules.push_back(module);
	return module;

}