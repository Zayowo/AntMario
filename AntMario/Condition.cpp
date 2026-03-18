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

bool Condition::HasPickedFireFlower(PlayerContext& ctx)
{

	bool hasPickedFireFlower = ctx.hasPickedFireFlower;
	ctx.hasPickedFireFlower = false;

	if (hasPickedFireFlower)
	{
		return true;
	}

	return false;

}

bool Condition::IsHitByEnemy(PlayerContext& ctx)
{

	bool isHitByEnemy = ctx.isHitByEnemy;
	ctx.isHitByEnemy = false;

	if (isHitByEnemy && ctx.invulnerability <= 0.f)
	{
		ctx.invulnerability = 1.5f;
		return true;
	}

	return false;

}

bool Condition::IsHitByPlayer(TurtleContext& ctx)
{

	bool isHitByPlayer = ctx.isHitByPlayer;
	ctx.isHitByPlayer = false;

	if (isHitByPlayer)
	{
		return true;
	}

	return false;

}