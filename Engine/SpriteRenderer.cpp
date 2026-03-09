#include "SpriteRenderer.h"
#include "Engine.h"
#include "ResourceModule.h"

SpriteRenderer::SpriteRenderer(std::string path)
{

	ResourceModule* resourceModule = Engine::GetModule<ResourceModule>();

	if (!resourceModule)
		return;

	sf::Texture& texture = resourceModule->GetTexture(path);
	sprite = new sf::Sprite(texture);

};

void SpriteRenderer::Update(float dt)
{

	Transform& transform = owner->GetTransform();
	sprite->setPosition(transform.pos);
	sprite->setRotation(sf::degrees(transform.rot));
	sprite->setScale(transform.scale);

}

void SpriteRenderer::Render(sf::RenderWindow* window)
{

	window->draw(*sprite);

}
