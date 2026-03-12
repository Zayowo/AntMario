#include "FireComponent.h"
#include "Scene.h"
#include "SquareCollider.h"
#include <VelocityComponent.h>
#include <Engine.h>
#include <TimeModule.h>

void FireComponent::Init()
{
	SquareCollider* collider = owner->GetComponent<SquareCollider>();

	//collider->RegisterCollisionCallback("Collider", [this](GameObject* other) {touchGround(); });
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

	if (vector->GetVelocity().y == 0)
	{

		vector->SetY(-300);

	}

	if (vector->GetVelocity().x == 0)
	{

		ActualScene->DeleteGameObject(owner);

	}

	// s'il touche un mur -> delete
	
	// bondi quand il touche le sol

}

