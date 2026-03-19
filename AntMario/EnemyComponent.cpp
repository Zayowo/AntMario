#include <Scene.h>
#include <ResourceModule.h>
#include <SpriteRenderer.h>
#include <SquareCollider.h>
#include <Scene.h>
#include <VelocityComponent.h>
#include "EnemyComponent.h"
#include "BonusComponent.h"

void EnemyComponent::Init()
{

	SquareCollider* collider = owner->GetComponent<SquareCollider>();
	collider->RegisterCallback("Fireball", [this](GameObject* other) { Kill(); });

}


void EnemyComponent::Move()
{
	VelocityComponent* velocity = owner->GetComponent<VelocityComponent>();
	velocity->SetX(-1.f);
}

void EnemyComponent::Kill()
{

	Engine::GetModule<ResourceModule>()->PlaySound("Assets/Sounds/EnemyKill.wav", 0.75f, 1.f);
	sf::Vector2f pos = owner->GetTransform().pos + sf::Vector2f(0.f, -20.f);
	GameObject* orb = owner->GetScene()->CreateGameObject("BloodOrb", pos);

	orb->AddComponent<SpriteRenderer>("Assets/BloodOrb.png");
	orb->AddComponent<SquareCollider>(sf::Vector2f(20.f, 20.f));
	orb->AddComponent<BonusComponent>(BonusType::BLOOD_ORB);


	owner->GetScene()->DeleteGameObject(owner);

}