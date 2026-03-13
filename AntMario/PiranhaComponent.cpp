#include "PiranhaComponent.h"
#include <SquareCollider.h>
#include <Scene.h>

void PiranhaComponent::Init() {
	// position au sol + offset ?
	owner->GetTransform().origin = { 0.f, 0.f };
	yOrigin = owner->GetTransform().pos.y;

	SquareCollider* collider = owner->GetComponent<SquareCollider>();

	collider->RegisterCallback("Fireball", [this](GameObject* o) { TouchByBall(o); });

}

void PiranhaComponent::Update(float dt)
{
	// deplacement du sol sortie complete 'en fonction du sprite
	if (isMoving == false) {
		std::cout << cooldown << std::endl;
		cooldown += dt;
	}

	if (cooldown > 2.f) {
		
		isMoving = true;

		if (isOut) {
			owner->GetTransform().pos.y += speed * dt;
		}
		else {
			owner->GetTransform().pos.y -= speed * dt;
		}
		
		y += speed * dt;

		if (y >= max) {
			y = 0;

			isMoving = false;
			cooldown = 0.f;
			isOut = !isOut;



		}

	}
}

void PiranhaComponent::TouchByBall(GameObject* other) {
	std::cout << "test" << std::endl;
	other->GetScene()->DeleteGameObject(other);
	owner->GetScene()->DeleteGameObject(owner);
}
