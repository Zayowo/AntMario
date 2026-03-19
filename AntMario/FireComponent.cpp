#include "FireComponent.h"
#include "Scene.h"
#include "SquareCollider.h"
#include <VelocityComponent.h>
#include <Engine.h>
#include <TimeModule.h>

void FireComponent::Init()
{
	VelocityComponent* velocity = owner->GetComponent<VelocityComponent>();
	if (velocity)
	{

		velocity->RegisterHit("Terrain", VelocityHitType::LEFT, [this](GameObject* terrain) {
			owner->GetScene()->DeleteGameObject(owner);
		});

		velocity->RegisterHit("Terrain", VelocityHitType::RIGHT, [this](GameObject* terrain) {
			owner->GetScene()->DeleteGameObject(owner);
		});

	}

	SquareCollider* collider = owner->GetComponent<SquareCollider>();

	if (collider)
	{
		collider->RegisterCallback("Goomba", [this](GameObject* other) {
			owner->GetScene()->DeleteGameObject(owner);
		});

		collider->RegisterCallback("Turtle", [this](GameObject* other) {
			owner->GetScene()->DeleteGameObject(owner);
		});

		collider->RegisterCallback("Piranha", [this](GameObject* other) {
			owner->GetScene()->DeleteGameObject(owner);
		});
	}
}

void FireComponent::Update(float dt)
{
	// s'il sort de la fenetre -> delete
	sf::Vector2f center = Engine::GetModule<WindowModule>()->GetRenderWindow()->getView().getCenter();
	VelocityComponent* vector = owner->GetComponent<VelocityComponent>();
	Scene* ActualScene = owner->GetScene();

	float distance = (center - owner->GetTransform().pos).length();

	if (distance > 750.f)
	{
		ActualScene->DeleteGameObject(owner);
		return;
	}

	// Rebondir quand la fireball touche le sol
	if (vector->GetVelocity().y == 0)
	{
		vector->SetY(-350);
	}
}

