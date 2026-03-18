#include <SquareCollider.h>
#include <SpriteRenderer.h>
#include <VelocityComponent.h>
#include "BigState.h"

void BigState::Enter(PlayerContext& ctx)
{

	ctx.player->GetComponent<SquareCollider>()->SetSize(sf::Vector2f(40.f, 115.f));
	ctx.player->GetComponent<SpriteRenderer>()->SetAnimationRule(SpriteAnimationRule(sf::Vector2i(0, 128), sf::Vector2i(128, 128), 4));
	ctx.isWalking = false;
	ctx.isInMushroom = true;

}

void BigState::Execute(PlayerContext& ctx, float dt)
{

	if (ctx.invulnerability > 0) {
		ctx.invulnerability -= dt;
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
