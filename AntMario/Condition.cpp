#include "Condition.h"
#include "SquareCollider.h"


bool Condition::collisionWithEnemy(PlayerContext& p)
{
	SquareCollider* colideP = p.player->GetComponent<SquareCollider>();
	for (GameObject* enemy : p.enemies) {
		if (colideP->IsColliding(enemy) && p.invulnerability <= 0) {
			p.invulnerability = 1.5f;
			return true;
		}
	}
	return false;
	
}
