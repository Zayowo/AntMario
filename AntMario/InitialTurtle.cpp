#include <SpriteRenderer.h>
#include <VelocityComponent.h>
#include "InitialTurtle.h"
#include "GoombaComponent.h"

void InitialTurtle::Enter(TurtleContext& ctx)
{
	VelocityComponent* velocity = ctx.turtle->GetComponent<VelocityComponent>();
	ctx.turtle->GetComponent<SpriteRenderer>()->SetAnimationRule(SpriteAnimationRule(sf::Vector2i(0, 0), sf::Vector2i(67, 30), 3));
	velocity->RegisterHit("Goomba", VelocityHitType::LEFT, [this](GameObject* other) { ChangeDirection(other, -1); });
	velocity->RegisterHit("Goomba", VelocityHitType::RIGHT, [this](GameObject* other) { ChangeDirection(other, 1); });
}

void InitialTurtle::Execute(TurtleContext& ctx, float dt)
{

	Transform& transform = ctx.turtle->GetTransform();
	VelocityComponent* velocity = ctx.turtle->GetComponent<VelocityComponent>();

	if (!velocity)
		std::cerr << "TurtleComponent : missing VelocityComponent" << std::endl;

	velocity->SetX(-1.f);

	float velocityX = velocity->GetVelocity().x;
	if (velocityX != 0.f)
		transform.scale.x = abs(transform.scale.x) * (velocityX > 0.f ? 1 : -1);

}


void InitialTurtle::ChangeDirection(GameObject* other, float dir)
{
	
	other->GetComponent<GoombaComponent>()->ChangeDirection(dir);
}