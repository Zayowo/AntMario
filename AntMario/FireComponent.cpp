#include "FireComponent.h"
#include "Scene.h"
#include "SquareCollider.h"
#include <VelocityComponent.h>
#include <Engine.h>
#include <TimeModule.h>

void FireComponent::Init()
{
	SquareCollider* collider = owner->GetComponent<SquareCollider>();

	collider->RegisterCollisionCallback("Collider", [this](GameObject* other) {touchGround(); });
}

void FireComponent::Update(float dt)
{
	// s'il sort de la fenetre -> delete

	VelocityComponent* vector = owner->GetComponent<VelocityComponent>();
	Scene* ActualScene = owner->GetScene();

	sf::Vector2f windowSize = { 1200, 800 };
	sf::Vector2f position = owner->GetTransform().pos;
	if (position.x <= 0 || position.x >= 1200 ||
		position.y <= 0 || position.y >= 800) {
		ActualScene->DeleteGameObject(owner);
	}

	// s'il touche un mur -> delete
	
	// bondi quand il touche le sol

}

void FireComponent::touchGround() {
	//bond
	VelocityComponent* vector = owner->GetComponent<VelocityComponent>();
	sf::Vector2f velocity = vector->GetVelocity();

	

	float direction = 0;
	if (owner->GetTransform().scale.x < 0)
		direction = -1.f;
	else
		direction = 1.f;

	std::cout << direction << std::endl;

	float dt = Engine::GetModule<TimeModule>()->GetDeltaTime();
	if (velocity.y <= 0) {
		std::cout << - (300000 * dt) << std::endl;
		vector->SetVelocity({ velocity.x, - (300000*dt) });
	}
}
