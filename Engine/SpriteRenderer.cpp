#include <iostream>
#include "SpriteRenderer.h"
#include "Engine.h"
#include "ResourceModule.h"
#include "Utils.h"

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
	sf::FloatRect bounds = sprite->getLocalBounds();
	
	sprite->setPosition(transform.pos);
	sprite->setRotation(sf::degrees(transform.rot));
	sprite->setScale(transform.scale);
	sprite->setOrigin(sf::Vector2f(
		bounds.size.x * transform.origin.x,
		bounds.size.y * transform.origin.y
	));
	
	if (_animationRule.has_value())
	{
		SpriteAnimationRule& rule = _animationRule.value();
		animationTime += dt;

		float totalDuration = rule.frames * 0.1f;
		float currentTimeInLoop = fmod(animationTime, totalDuration);
		int frame = int(currentTimeInLoop / 0.1f);

		sprite->setTextureRect({ { rule.pos.x + (rule.size.x * frame), rule.pos.y }, rule.size });

	}

}

void SpriteRenderer::Render(sf::RenderWindow* window)
{

	window->draw(*sprite);

}

void SpriteRenderer::SetTextureRect(sf::IntRect rect)
{

	sprite->setTextureRect(rect);

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

void SpriteRenderer::SetTexture(std::string path)
{

	this->path = path;
	ResourceModule* resourceModule = Engine::GetModule<ResourceModule>();
	sf::Texture& texture = resourceModule->GetTexture(path);
	sprite->setTexture(texture);

}