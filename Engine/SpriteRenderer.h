#pragma once
#include "Component.h"
class SpriteRenderer : public Component
{
	void Update() override;

	void Render() override;



private:
	sf::Sprite sprite;
};

