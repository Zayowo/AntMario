#include "SceneModule.h"

void SceneModule::Update()
{
	for (Scene* scene : scenes) {
		scene->Update();
	}
}

void SceneModule::Render()
{
	for (Scene* scene : scenes) {
		scene->Render();
	}
}

void SceneModule::PushStack(Scene* scene)
{
	scenes.push_back(scene);
}

void SceneModule::PopStack()
{
	scenes.pop_back();
}
