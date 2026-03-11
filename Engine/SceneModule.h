#pragma once
#include <unordered_map>
#include <functional>
#include <vector>
#include "Module.h"
#include "Scene.h"

class SceneModule : public Module
{

public:
	void Update() override;
	void Render() override;
	void Destroy() override;


	// Ajoute une scène dans la sceneStack
	void PushScene(std::string name);

	// Enlève la scène la plus récente dans la sceneStack
	void PopScene();

	// Applique une scène en enlevant les scènes actuelles
	void SetScene(std::string name);

	// Enregistre une scène
	template<typename SceneType>
	void RegisterScene(std::string name);

private:
	std::vector<Scene*> sceneStack;
	std::unordered_map<std::string, std::function<Scene* ()>> sceneConstructorMap;

};

#include "SceneModule.inl"