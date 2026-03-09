#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
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
	void Update(float dt);
	void Render(sf::RenderWindow* window);
	void Destroy();


	std::string GetName();
	Transform& GetTransform();
	
	template<typename ComponentType>
	ComponentType* GetComponent();

	template<typename ComponentType, typename... Param>
	ComponentType* AddComponent(Param ... parameters);

protected:
	std::vector<Component*> components;
	std::string name;
	Transform transform;

};

#include "GameObject.inl"