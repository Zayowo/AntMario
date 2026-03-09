#pragma once
#include <SFML/Graphics.hpp>
#include "Module.h"

class TimeModule : public Module
{

public:
	void Init() override;
	void Update() override;

private:
	sf::Clock deltaClock;
	float dt = 0;

};

