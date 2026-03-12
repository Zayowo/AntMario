#pragma once
#include <functional>
#include "Component.h"
#include "VelocityHitType.h"

class VelocityComponent : public Component
{

public:
	VelocityComponent(float speed);

	void Init();
	void Update(float dt) override;

	// Applique une vélocité
	void SetVelocity(sf::Vector2f velocity);

	// Applique une vélocité sur un axe x ou y
	void SetX(float x);
	void SetY(float y);

	/*void SetTrajector(std::function<void> tj);*/

	// Récupère la vélocité actuelle
	sf::Vector2f GetVelocity();

	// Enregistre un callback lorsque la vélocité entre en collision avec un nom de collider dans une certaine direction
	void RegisterHit(std::string name, VelocityHitType hitType, std::function<void(GameObject*)> callback);

private:
	float speed;
	sf::Vector2f velocity = sf::Vector2f(0.f, 0.f);

	// Résous les collisions lorsque le game object entre en collisions avec un block (et pas que)
	void ResolveCollisions(GameObject* other);

	// Envoie les callbacks enregistrés dans le hitCallbackMap en fonction du type de collision
	void SendHit(GameObject* other, VelocityHitType hitType);

};