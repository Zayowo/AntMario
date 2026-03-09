#pragma once
#include "GameObject.h"
class Component
{
public:
	virtual void Init() {};
	virtual void Update() {};
	virtual void Render() {};
	virtual void Destroy() {};
	GameObject* GetOwner() {};
protected:
	GameObject* owner;

};

