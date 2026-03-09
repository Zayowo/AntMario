#pragma once
#include <SFML/Graphics.hpp>

struct SpriteAnimationRule
{

	SpriteAnimationRule(sf::Vector2i pos, sf::Vector2i size, int frames) : SpriteAnimationRule(pos, size, frames, 1.f) {};
	SpriteAnimationRule(sf::Vector2i pos, sf::Vector2i size, int frames, float speed) : pos(pos), size(size), frames(frames), speed(speed) {};

	sf::Vector2i pos;
	sf::Vector2i size;
	int frames;
	float speed;

};