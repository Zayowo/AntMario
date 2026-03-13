#include "Condition.h"
#include "SquareCollider.h"
#include <Scene.h>


bool Condition::collisionWithEnemy(PlayerContext& p)
{

	SquareCollider* colideP = p.player->GetComponent<SquareCollider>();

	std::vector<GameObject*> goombas = p.player->GetScene()->GetGameObjectsByName("Goomba");
	
	for (GameObject* enemy : goombas) {
		if (colideP->IsColliding(enemy) && p.invulnerability <= 0) {
			p.invulnerability = 1.5f;
			return true;
		}
	}
	return false;
	
}

bool Condition::collitionWithFireBonus(PlayerContext& p)
{
	SquareCollider* playerCollider = p.player->GetComponent<SquareCollider>();
	Scene* scene = p.player->GetScene();
	std::vector<GameObject*> allBonus= scene->GetGameObjectsByName("Bonus3");
	for (GameObject* fireBonus : allBonus) {
		if (playerCollider->IsColliding(fireBonus)) {
			return true;
		}
	}

	return false;
		
}

bool Condition::collitionWithBigBonus(PlayerContext& p)
{
	SquareCollider* playerCollider = p.player->GetComponent<SquareCollider>();
	Scene* scene = p.player->GetScene();
	std::vector<GameObject*> allBonus = scene->GetGameObjectsByName("Bonus2");
	for (GameObject* bigBonus : allBonus) {
		if (playerCollider->IsColliding(bigBonus)) {
			return true;
		}
	}
	return false;
}

bool Condition::collisionWithPlayer(TurtleContext& t)
{
	t.turtle->GetComponent<SquareCollider>();
	return false;
}


