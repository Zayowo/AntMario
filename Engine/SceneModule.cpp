#include "SceneModule.h"
#include "Engine.h"
#include "WindowModule.h"
#include "TimeModule.h"

void SceneModule::Update()
{

	float dt = Engine::GetModule<TimeModule>()->GetDeltaTime();

	for (Scene* scene : sceneStack)
		scene->Update(dt);

}

void SceneModule::Render()
{

	sf::RenderWindow* window = Engine::GetModule<WindowModule>()->GetRenderWindow();

	for (Scene* scene : sceneStack)
		scene->Render(window);

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
	sceneStack.emplace_back(scene);

}

void SceneModule::PopScene()
{

	sceneStack.pop_back();

}

void SceneModule::SetScene(std::string name)
{

	if (!sceneConstructorMap[name])
		return;

	Scene* scene = sceneConstructorMap[name]();
	sceneStack.clear();
	sceneStack.emplace_back(scene);

}