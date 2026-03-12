#pragma once
#include <SFML/System.hpp>
#include "Module.h"

class TimeModule : public Module
{

public:
	void Init() override;
	void Update() override;

	// Récupère le deltaTime
	float GetDeltaTime();

	// Récupère la vitesse (en référence, eheh)
	float& GetSpeed();

private:
	sf::Clock deltaClock;
	float speed = 1.f;
	float dt = 0.f;

};

