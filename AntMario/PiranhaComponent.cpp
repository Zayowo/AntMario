#include "PiranhaComponent.h"

void PiranhaComponent::Init() {
	// position au sol + offset ?
	owner->GetTransform().origin = { 0.f, 0.f };
	yOrigin = owner->GetTransform().pos.y;
}

void PiranhaComponent::Update(float dt)
{
	// deplacement du sol sortie complete 'en fonction du sprite
	if (isMove == false) {
		cooldown += dt;
	}

	if (cooldown > 3.f) {
		isMove = true;


		if (y >= max) {
			y = 0;

			isMove = false;
		}
	}
}
