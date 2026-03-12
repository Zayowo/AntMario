#include <Engine.h>
#include <ResourceModule.h>
#include <Scene.h>
#include "BackgroundElement.h"

BackgroundElement::BackgroundElement(std::string path, float depth, sf::Vector2f offset) :
	depth(depth),
	offset(offset)
{

	ResourceModule* resourceModule = Engine::GetModule<ResourceModule>();
	sf::Texture& texture = resourceModule->GetTexture(path);
	sprite = new sf::Sprite(texture);

}

void BackgroundElement::Init()
{

	player = owner->GetScene()->GetGameObjectsByName("Player")[0];

}

void BackgroundElement::Update(float dt)
{

}

void BackgroundElement::Render(sf::RenderWindow* window)
{

	sf::View view = window->getView();
	Transform& transform = owner->GetTransform();
	sf::Vector2f elementPos = sf::Vector2f(
		transform.pos.x + offset.x + view.getCenter().x * depth,
		transform.pos.y + offset.y
	);

	sprite->setPosition(elementPos);
	sprite->setRotation(sf::degrees(transform.rot));
	sprite->setScale(transform.scale);
	sprite->setOrigin(sprite->getLocalBounds().size * 0.5f);

	window->draw(*sprite);

}