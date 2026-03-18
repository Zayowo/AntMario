#include "GoombaComponent.h"
#include <VelocityComponent.h>
#include <SquareCollider.h>
#include <Scene.h>

void GoombaComponent::Init() {
	//recupere les initialisation en commun
	EnemyComponent::Init();
	SquareCollider* collider = owner->GetComponent<SquareCollider>();
	
	velocityComponent = owner->GetComponent<VelocityComponent>();
	if (!velocityComponent) std::cerr << "GoombaComponent: No VelocityComponent detected!" << std::endl;

	velocityComponent->RegisterHit("Terrain", VelocityHitType::LEFT, [this](GameObject* other) { ChangeDirection(-1.f); });
	velocityComponent->RegisterHit("Terrain", VelocityHitType::RIGHT, [this](GameObject* other) { ChangeDirection(1.f); });

	velocityComponent->RegisterHit("Goomba", VelocityHitType::LEFT, [this](GameObject* other) { ChangeDirection(-1.f); });
	velocityComponent->RegisterHit("Goomba", VelocityHitType::RIGHT, [this](GameObject* other) { ChangeDirection(1.f); });

	velocityComponent->RegisterHit("Turtle", VelocityHitType::LEFT, [this](GameObject* other) { Destroy(other); });
	velocityComponent->RegisterHit("Turtle", VelocityHitType::RIGHT, [this](GameObject* other) { Destroy(other); });

}

void GoombaComponent::Update(float dt)
{

	velocityComponent->SetX(direction);

}


void GoombaComponent::StepByPlayer(GameObject* other)
{
	VelocityComponent* otherVelocityComponent = other->GetComponent<VelocityComponent>();
	otherVelocityComponent->SetY(-350.f);
	owner->GetScene()->DeleteGameObject(owner);

}

void GoombaComponent::ChangeDirection(float direction)
{

	this->direction = direction;

}

void GoombaComponent::Destroy(GameObject* other) {
	owner->GetScene()->DeleteGameObject(owner);
}