#pragma once
#include <Component.h>
#include "GameController.h"

class PlayerController : public Component
{

public:
	void Init()override;
	void Update(float dt) override;
	
	// Collision avec un block intéragissable
	void HitInteractableBlock(GameObject* block);

	// Récupère un bonus
	void PickUp(GameObject* bonus);

	// Écrase un goomba
	void StepOnGoomba(GameObject* goomba);

private:
	bool isDoubleJump = false;
	GameController* gameController;

};