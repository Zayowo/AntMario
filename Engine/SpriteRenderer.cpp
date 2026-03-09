#include "SpriteRenderer.h"

void SpriteRenderer::Update()
{
	sprite.setPosition(owner->GetTransform().pos);
}

void SpriteRenderer::Render()
{

}
