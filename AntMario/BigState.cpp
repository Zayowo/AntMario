#include <SquareCollider.h>
#include <SpriteRenderer.h>
#include <VelocityComponent.h>
#include "BigState.h"

void BigState::Enter(PlayerContext& ctx)
{

	ctx.player->GetComponent<SquareCollider>()->SetSize(sf::Vector2f(30.f, 115.f));
	ctx.isWalking = false;
	ctx.isInMushroom = true;

}

void BigState::Execute(PlayerContext& ctx, float dt)
{

	SpriteRenderer* spriteRenderer = ctx.player->GetComponent<SpriteRenderer>();

	if (ctx.invulnerability > 0) {
		ctx.invulnerability -= dt;
		// Flash effect during invulnerability
		int flashCount = (int)(ctx.invulnerability * 4); // Flash 4 times per second
		if (flashCount % 2 == 0) {
			sf::Color color = spriteRenderer->GetColor();
			color.a = 100; // Semi-transparent
			spriteRenderer->SetColor(color);
		} else {
			sf::Color color = spriteRenderer->GetColor();
			color.a = 255; // Full opacity
			spriteRenderer->SetColor(color);
		}
	} else {
		// Make sure sprite is fully visible after invulnerability ends
		sf::Color color = spriteRenderer->GetColor();
		color.a = 255;
		spriteRenderer->SetColor(color);
	}

	const float velocityX = ctx.player->GetComponent<VelocityComponent>()->GetVelocity().x;
	if (velocityX != 0.f && !ctx.isWalking)
	{
		ctx.isWalking = true;
		ctx.player->GetComponent<SpriteRenderer>()->SetAnimationRule(SpriteAnimationRule(sf::Vector2i(0, 128), sf::Vector2i(128, 128), 4));
	}
	else if (velocityX == 0.f && ctx.isWalking)
	{
		ctx.isWalking = false;
		ctx.player->GetComponent<SpriteRenderer>()->SetAnimationRule(SpriteAnimationRule(sf::Vector2i(0, 128), sf::Vector2i(128, 128), 1));
	}

}

void BigState::Exit(PlayerContext& ctx)
{

	ctx.isInMushroom = false;

}
