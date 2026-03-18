#include <SpriteRenderer.h>
#include <VelocityComponent.h>
#include "InitialTurtle.h"

void InitialTurtle::Enter(TurtleContext& ctx)
{

	ctx.turtle->GetComponent<SpriteRenderer>()->SetAnimationRule(SpriteAnimationRule(sf::Vector2i(0, 0), sf::Vector2i(135, 60), 3));

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

