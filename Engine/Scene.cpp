#include "Scene.h"

void Scene::Init()
{

	for (GameObject* gameObject : gameObjects)
		gameObject->Init();

}

void Scene::Update()
{

	for (GameObject* gameObject : gameObjects)
		gameObject->Update();

}

void Scene::Render()
{

	for (GameObject* gameObject : gameObjects)
		gameObject->Render();

}

void Scene::Destroy()
{

	for (GameObject* gameObject : gameObjects)
		gameObject->Destroy();

}