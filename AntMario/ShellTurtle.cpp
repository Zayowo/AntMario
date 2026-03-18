#include "ShellTurtle.h"
#include "SpriteRenderer.h"
#include "SquareCollider.h"
#include "VelocityComponent.h"
#include "Condition.h"
#include <Scene.h>

void ShellTurtle::Enter(TurtleContext& ctx)
{

	ctx.turtle->GetComponent<SquareCollider>()->SetSize(sf::Vector2f(40.f, 40.f));
	ctx.turtle->GetComponent<VelocityComponent>()->SetX(0.f);
	ctx.turtle->GetComponent<SpriteRenderer>()->SetAnimationRule(SpriteAnimationRule(sf::Vector2i(0, 60), sf::Vector2i(64, 64), 7));

}

void ShellTurtle::Execute(TurtleContext& ctx, float dt)
{

	Transform& transform = ctx.turtle->GetTransform();
	VelocityComponent* velocity = ctx.turtle->GetComponent<VelocityComponent>();

	if (IsHitByPlayer(ctx) && !isMoving) {
		float dir = ctx.player->GetTransform().scale.x;
		velocity->SetX(dir * 3);
		isMoving = true;
	}

	if (velocity->GetVelocity().x == 0 && isMoving == true)
	{
		isMoving = false;
		ctx.turtle->GetScene()->DeleteGameObject(ctx.turtle);
	}

	float velocityX = velocity->GetVelocity().x;
	if (velocityX != 0.f)
		transform.scale.x = abs(transform.scale.x) * (velocityX > 0.f ? 1 : -1);

}

bool ShellTurtle::IsHitByPlayer(TurtleContext& ctx)
{

	bool isHitByPlayer = ctx.isHitByPlayer;
	ctx.isHitByPlayer = false;

	if (isHitByPlayer)
	{
		return true;
	}

	return false;

}
