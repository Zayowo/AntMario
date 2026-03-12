#include <iostream>
#include "SpriteRenderer.h"
#include "Engine.h"
#include "ResourceModule.h"

SpriteRenderer::SpriteRenderer(std::string path) :
	path(path)
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
	sprite->setOrigin(sf::Vector2f(
		sprite->getLocalBounds().size.x * transform.origin.x,
		sprite->getLocalBounds().size.y * transform.origin.y
	));
	
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

void SpriteRenderer::SetTiling(sf::Vector2f size, bool isTiled)
{

	sprite->setTextureRect({ { 0, 0 }, (sf::Vector2i)size });
	ResourceModule* resourceModule = Engine::GetModule<ResourceModule>();
	sf::Texture& texture = resourceModule->GetTexture(path);
	texture.setRepeated(isTiled);

}

void SpriteRenderer::SetAnimationRule(const SpriteAnimationRule animationRule)
{

	_animationRule = std::make_optional(animationRule);
	animationTime = 0.f;

}