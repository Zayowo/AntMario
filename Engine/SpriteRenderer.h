#pragma once
#include "Component.h"
#include "SpriteAnimationRule.h"

class SpriteRenderer : public Component
{

public:
	SpriteRenderer(std::string path);

	void Update(float dt) override;
	void Render(sf::RenderWindow* window) override;

	// Applique une SpriteAnimationRule
	void SetAnimationRule(SpriteAnimationRule animationRule);

private:
	sf::Sprite* sprite = nullptr;
	std::optional<SpriteAnimationRule> _animationRule;
	float animationTime = 0.f;

};
