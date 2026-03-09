#pragma once
#include <iostream>
#include <SFML/Graphics.hpp>
#include <vector>

class Component;

struct Transform {
	sf::Vector2f pos;
	float rot;
	sf::Vector2f scale;
};

class GameObject
{

public:
	void Init();
	void Update();
	void Render();
	void Destroy();


	std::string GetName();
	Transform& GetTransform();
	
	template<typename ComponentType>
	ComponentType* GetComponent();

	template<typename ComponentType, typename... Param>
	ComponentType* AddComponent(Param ... parameters);

private:
	std::vector<Component*> components;
	std::string name;
	Transform transform;

};

#include "GameObject.inl"