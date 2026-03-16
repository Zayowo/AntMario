#pragma once
#include <Component.h>
#include "GameController.h"
#include "FSMComponent.h"
#include "PlayerContext.h"

class PlayerController : public Component
{

public:
	void Init()override;
	void Update(float dt) override;
	
	// Collision avec un block intéragissable
	void HitInteractableBlock(GameObject* block);

	// Récupère un bonus
	void PickUp(GameObject* bonus);

	// Marche à l'envers sur un block "ReverseWalk"
	void WalkUpsideDown(GameObject* block);

	// Fait rebondir le joueur (Par exemple sur un enemy)
	void BouncePlayer();

	// Tente d'éliminer un enemy (si c'est un game object valide!)
	static void KillEnemy(GameObject* enemy);

	// Quand il se fait tabasser par un ennemi, t'as capté
	void HitByEnemy(GameObject* enemy);


private:
	bool isDoubleJump = false;
	InputModule* inputModule;
	GameController* gameController;
	VelocityComponent* velocityComponent;
	SquareCollider* collider;
	FSMComponent<PlayerContext>* fsm;

};