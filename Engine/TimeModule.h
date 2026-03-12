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

private:
	sf::Clock deltaClock;
	float dt = 0.f;

};

