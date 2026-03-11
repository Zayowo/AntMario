#pragma once
#include <SFML/System.hpp>

struct Transform
{

	sf::Vector2f pos = sf::Vector2f(0.f, 0.f);
	float rot = 0.f;
	sf::Vector2f scale = sf::Vector2f(1.f, 1.f);
	sf::Vector2f origin = sf::Vector2f(0.5f, 0.5f);

};