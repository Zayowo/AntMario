#include <iostream>
#include "SpriteRenderer.h"
#include "Engine.h"
#include "ResourceModule.h"

SpriteRenderer::SpriteRenderer(std::string path)
{

	ResourceModule* resourceModule = Engine::GetModule<ResourceModule>();
	sf::Texture& texture = resourceModule->GetTexture(path);
	sprite = new sf::Sprite(texture);

};

void SpriteRenderer::Update(float dt)
{

	Transform& transform = owner->GetTransform();
	sprite->setPosition(transform.pos);
	sprite->setRotation(sf::degrees(transform.rot));
	sprite->setScale(transform.scale);
	sprite->setOrigin(sprite->getLocalBounds().size * 0.5f);

	if (_animationRule.has_value())
	{
		SpriteAnimationRule& rule = _animationRule.value();
		animationTime += dt;
		sprite->setTextureRect({ { rule.pos.x + rule.size.x, rule.pos.y }, rule.size });

	}

}

void SpriteRenderer::Render(sf::RenderWindow* window)
{

	window->draw(*sprite);

}


void SpriteRenderer::SetAnimationRule(const SpriteAnimationRule animationRule)
{

	_animationRule = std::make_optional(animationRule);
	animationTime = 0.f;

}