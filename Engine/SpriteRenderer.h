#pragma once
#include "Component.h"
#include "SpriteAnimationRule.h"

class SpriteRenderer : public Component
{

public:
	SpriteRenderer(std::string path);

	void Update(float dt) override;
	void Render(sf::RenderWindow* window) override;

	// Applique une texture rect
	void SetTextureRect(sf::IntRect rect);

	// Applique une taille au sprite, et si elle est répété ou non
	void SetTiling(sf::Vector2f size, bool isTiled);

	// Applique une SpriteAnimationRule
	void SetAnimationRule(SpriteAnimationRule animationRule);

	// Applique une nouvelle texture
	void SetTexture(std::string path);

private:
	std::string path;
	sf::Sprite* sprite = nullptr;
	std::optional<SpriteAnimationRule> _animationRule;
	float animationTime = 0.f;

};