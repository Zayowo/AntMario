#pragma once
#include <functional>
#include "Component.h"

class SquareCollider : public Component
{

public:
	SquareCollider(sf::Vector2f size);

	void Update(float dt) override;
	void Render(sf::RenderWindow* window) override;

	// Vérifie si le collider est en collision avec un autre collider d'un game object
	bool IsColliding(GameObject* gameObject);

	// Enregistre un callback lorsque le collider est en collision avec un autre collider d'un game object avec un nom spécifique
	void RegisterCollisionCallback(std::string name, std::function<void(GameObject*)> callback);

private:
	sf::RectangleShape* shape;
	std::unordered_map<std::string, std::vector<std::function<void(GameObject*)>>> collisionCallbackMap;

};