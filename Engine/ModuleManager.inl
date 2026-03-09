
template<typename ModuleType>
Module* ModuleManager::CreateModule()
{

	ModuleType* module = new ModuleType();
	modules.push_back(module);

}