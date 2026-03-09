#pragma once
#include "GameObject.h"

class Component
{
	friend class GameObject;

public:
	virtual void Init() {};
	virtual void Update(float dt) {};
	virtual void Render(sf::RenderWindow* window) {};
	virtual void Destroy() {};

	// Récupère le game object qui possède ce component
	GameObject* GetOwner();

protected:
	GameObject* owner;

};

