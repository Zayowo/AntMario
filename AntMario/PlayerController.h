#pragma once
#include <Component.h>
#include "GameController.h"

class PlayerController : public Component
{

public:
	void Init()override;
	void Update(float dt) override;
	
	// Casse une brick
	void BreakBrick(GameObject* brick);

	// Récupère un bonus
	void PickUp(GameObject* bonus);

private:
	bool isDoubleJump = false;
	GameController* gameController;

};