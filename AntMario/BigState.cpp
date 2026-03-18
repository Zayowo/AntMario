#include "BigState.h"
#include <SquareCollider.h>

void BigState::Enter(PlayerContext& ctx)
{

	ctx.player->GetTransform().scale = sf::Vector2f(1.f, 1.f);
	ctx.isInMushroom = true;

}

void BigState::Execute(PlayerContext& ctx, float dt)
{

	if (ctx.invulnerability > 0) {
		ctx.invulnerability -= dt;
	}


}

void BigState::Exit(PlayerContext& ctx)
{

	ctx.isInMushroom = false;

}
