#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>
#include "Transform.h"

class Scene;
class Component;

class GameObject
{

public:
	GameObject(std::string name, Scene* scene);

	void Init();
	void Update(float dt);
	void Render(sf::RenderWindow* window);
	void Destroy();

	// Récupère le nom du game object
	std::string GetName();

	// Récupère la scène dans laquel le game object est situé
	Scene* GetScene();

	// Récupère le transform du game object
	Transform& GetTransform();
	
	// Applique si le game object est tout le temps chargé ou non
	void SetIsAlwaysLoaded(bool isAlwaysLoaded);

	// Récupère un component de type
	template<typename ComponentType>
	ComponentType* GetComponent();

	// Ajoute un component de type
	template<typename ComponentType, typename... Param>
	ComponentType* AddComponent(Param... parameters);

protected:
	std::string name;
	Scene* scene;
	Transform transform;
	bool isAlwaysLoaded = false;
	std::vector<Component*> components;

};

#include "GameObject.inl"