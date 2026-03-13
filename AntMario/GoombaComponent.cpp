#include "GoombaComponent.h"
#include <VelocityComponent.h>
#include <SquareCollider.h>
#include <Scene.h>

void GoombaComponent::Init() {
	//recupere les initialisation en commun
	EnemyComponent::Init();
	SquareCollider* collider = owner->GetComponent<SquareCollider>();
	
}

void GoombaComponent::Update(float dt)
{
	EnemyComponent::Move();
}


void GoombaComponent::StepByPlayer(GameObject* other)
{
	VelocityComponent* otherVelocityComponent = other->GetComponent<VelocityComponent>();
	otherVelocityComponent->SetY(-350.f);
	owner->GetScene()->DeleteGameObject(owner);

}