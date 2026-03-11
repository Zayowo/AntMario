#pragma once
#include <functional>
#include "Component.h"

class ButtonRenderer : public Component
{

public:
	ButtonRenderer(std::string unhoveredPath, std::string hoveredPath, std::string string, std::function<void()> callback);

	void Update(float dt) override;
	void Render(sf::RenderWindow* window) override;

private:
	sf::Texture* unhoveredTexture;
	sf::Texture* hoveredTexture;
	sf::Sprite* sprite;
	sf::Text* text;
	std::function<void()> callback;

};