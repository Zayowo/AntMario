#include "LittleState.h"
#include "SquareCollider.h"

void LittleState::Enter(PlayerContext& pc)
{
	// recupere le transforme et le square colider = le mettre a une certaine taille
	pc.player->GetTransform().scale = sf::Vector2f(1.f, 0.6f);


}

void LittleState::Execute(PlayerContext& pc, float dt)
{
	if (pc.invulnerability > 0) {
		pc.invulnerability -= dt;
	}

}

void LittleState::Exit(PlayerContext& pc)
{

}
