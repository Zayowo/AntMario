#pragma once
#include <SFML/Graphics.hpp>
#include "Module.h"

class TimeModule : public Module
{
	void Init() override;

private :
	sf::Clock deltaClock;
};

