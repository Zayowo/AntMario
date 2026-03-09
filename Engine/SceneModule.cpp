#include "SceneModule.h"

void SceneModule::Update()
{

	for (Scene* scene : sceneStack)
		scene->Update();

}

void SceneModule::Render()
{

	for (Scene* scene : sceneStack)
		scene->Render();

}

void SceneModule::Destroy()
{

	for (Scene* scene : sceneStack)
		scene->Destroy();

}

void SceneModule::PushScene(std::string name)
{

	if (!sceneConstructorMap[name])
		return;

	Scene* scene = sceneConstructorMap[name]();
	sceneStack.push_back(scene);

}

void SceneModule::PopScene()
{

	sceneStack.pop_back();

}