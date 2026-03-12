#include "BigState.h"
#include <SquareCollider.h>

void BigState::Enter(PlayerContext& ctxP)
{
	ctxP.player->GetTransform().scale = sf::Vector2f(1.f, 1.f);
}

void BigState::Execute(PlayerContext& ctxP, float dt)
{
	if (ctxP.invulnerability > 0) {
		ctxP.invulnerability -= dt;
	}

}

void BigState::Exit(PlayerContext& ctxP)
{
}
