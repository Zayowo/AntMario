#include <SpriteRenderer.h>
#include <VelocityComponent.h>
#include "LittleState.h"
#include "SquareCollider.h"

void LittleState::Enter(PlayerContext& ctx)
{

	ctx.player->GetComponent<SquareCollider>()->SetSize(sf::Vector2f(40.f, 70.f));
	ctx.isWalking = false;

}

void LittleState::Execute(PlayerContext& ctx, float dt)
{

	if (ctx.invulnerability > 0) {
		ctx.invulnerability -= dt;
	}

	const float velocityX = ctx.player->GetComponent<VelocityComponent>()->GetVelocity().x;
	if (velocityX != 0.f && !ctx.isWalking)
	{
		ctx.isWalking = true;
		ctx.player->GetComponent<SpriteRenderer>()->SetAnimationRule(SpriteAnimationRule(sf::Vector2i(0, 0), sf::Vector2i(128, 128), 4));
	}
	else if (velocityX == 0.f && ctx.isWalking)
	{
		ctx.isWalking = false;
		ctx.player->GetComponent<SpriteRenderer>()->SetAnimationRule(SpriteAnimationRule(sf::Vector2i(0, 0), sf::Vector2i(128, 128), 1));
	}

}

void LittleState::Exit(PlayerContext& ctx)
{

}
