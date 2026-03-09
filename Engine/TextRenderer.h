#pragma once
#include <SFML/Graphics.hpp>
#include <string>
#include "Component.h"

class TextRenderer : public Component
{

public:
	TextRenderer(std::string string);

	void Update(float dt) override;
	void Render(sf::RenderWindow* window) override;

private:
	sf::Text* text;

};