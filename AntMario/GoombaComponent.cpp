#include <Scene.h>
#include <SpriteRenderer.h>
#include <SquareCollider.h>
#include <VelocityComponent.h>
#include "GoombaComponent.h"

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

	velocityComponent->RegisterHit("Turtle", VelocityHitType::LEFT, [this](GameObject* other) { ChangeDirection(-1.f); });
	velocityComponent->RegisterHit("Turtle", VelocityHitType::RIGHT, [this](GameObject* other) { ChangeDirection(1.f); });

	// Ajoute l'animation du "Goomba"
	SpriteRenderer* sprite = owner->GetComponent<SpriteRenderer>();
	if (!sprite)
		return;

	sprite->SetAnimationRule(SpriteAnimationRule(sf::Vector2i(0, 0), sf::Vector2i(128, 128), 4, 0.5f));

}

void GoombaComponent::Update(float dt)
{

	velocityComponent->SetX(direction);
	owner->GetTransform().scale = sf::Vector2f(direction * 0.5f, 0.5f);

}

void GoombaComponent::ChangeDirection(float direction)
{

	this->direction = direction;

}