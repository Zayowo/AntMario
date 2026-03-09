
template<typename SceneType>
void SceneModule::RegisterScene(std::string name)
{

	if (sceneConstructorMap[name])
		return;

	sceneConstructorMap[name] = []() {
		return new SceneType();
	};

}