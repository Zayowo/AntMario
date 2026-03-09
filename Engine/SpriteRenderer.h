#pragma once
#include "Component.h"

class SpriteRenderer : public Component
{

public:
	SpriteRenderer(std::string path);

	void Update(float dt) override;
	void Render(sf::RenderWindow* window) override;

private:
	sf::Sprite* sprite = nullptr;

};

