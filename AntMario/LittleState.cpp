#include "LittleState.h"
#include "SquareCollider.h"

void LittleState::Enter(PlayerContext& ctx)
{

	// recupere le transforme et le square colider = le mettre a une certaine taille
	ctx.player->GetTransform().scale = sf::Vector2f(1.f, 0.6f);

}

void LittleState::Execute(PlayerContext& ctx, float dt)
{

	if (ctx.invulnerability > 0) {
		ctx.invulnerability -= dt;
	}

}

void LittleState::Exit(PlayerContext& ctx)
{

}
