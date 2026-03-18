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

	sf::Vector2f center = Engine::GetModule<WindowModule>()->GetRenderWindow()->getView().getCenter();
	VelocityComponent* vector = owner->GetComponent<VelocityComponent>();
	Scene* ActualScene = owner->GetScene();

	sf::Vector2f windowSize = { 1200, 800 };
	float distance = (center - owner->GetTransform().pos).length();

	if (distance > 750.f)
	{
		ActualScene->DeleteGameObject(owner);
		return;
	}

	if (vector->GetVelocity().y == 0)
	{

		vector->SetY(-350);

	}

	if (vector->GetVelocity().x == 0)
	{

		ActualScene->DeleteGameObject(owner);

	}

	// s'il touche un mur -> delete
	
	// bondi quand il touche le sol

}

