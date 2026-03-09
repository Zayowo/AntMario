#pragma once
#include <iostream>
#include <vector>
#include "Module.h"
#include "Scene.h"


class SceneModule : public Module
{
public :
	void Update() override;
	void Render() override;
	void PushStack(Scene*);
	void PopStack();

private:
	std::vector<Scene*> scenes;
};

