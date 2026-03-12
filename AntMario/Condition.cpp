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

bool Condition::collitionWithFireBonus(PlayerContext& p)
{
	for (int i = 0; i < p.bonuses.size(); i++) {
		Bonus* temp = p.bonuses[i]->GetComponent<Bonus>();
		if (temp->getType() == BonusType::Bonus3) {
			p.bonuses.erase(p.bonuses.begin() + i);
			return true;
		}
	}

	return false;
}

bool Condition::collitionWithBigBonus(PlayerContext& p)
{
	
	
	for (int i = 0; i < p.bonuses.size(); i++) {
		Bonus* temp = p.bonuses[i]->GetComponent<Bonus>();
		if (temp->getType() == BonusType::Bonus2) {
			std::cout << "vrai ?" << std::endl;
			p.bonuses.erase(p.bonuses.begin() + i);
			return true;
		}
	}

	return false;
}
