#include "SpriteRenderer.h"

void SpriteRenderer::Update(float dt)
{
	sprite.setPosition(owner->GetTransform().pos);
}

void SpriteRenderer::Render(sf::RenderWindow* window)
{

}
