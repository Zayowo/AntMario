#include "Condition.h"
#include "SquareCollider.h"
#include <Scene.h>
#include "InitialTurtle.h"
#include <FSMComponent.h>
#include <VelocityComponent.h>
#include "ShellTurtle.h"


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

bool Condition::HasPickedMushroom(PlayerContext& ctx)
{

	bool hasPickedMushroom = ctx.hasPickedMushroom;
	ctx.hasPickedMushroom = false;

	if (hasPickedMushroom)
	{
		return true;
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

// C'est ignoble, mais c'est pas grave, au moins ça fait le taff
bool Condition::IsTurtleInInitialState(GameObject* turtle)
{

	return dynamic_cast<InitialTurtle*>(turtle->GetComponent<FSMComponent<TurtleContext>>()->GetState());

}

bool Condition::IsTurtleInShellWithoutMoving(GameObject* turtle)
{

	return dynamic_cast<ShellTurtle*>(turtle->GetComponent<FSMComponent<TurtleContext>>()->GetState()) &&
		turtle->GetComponent<VelocityComponent>()->GetVelocity().x == 0.f;

}