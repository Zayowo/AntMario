#include "ShellTurtle.h"
#include "SpriteRenderer.h"
#include "SquareCollider.h"
#include "VelocityComponent.h"
#include "Condition.h"
#include <Scene.h>

void ShellTurtle::Enter(TurtleContext& ctxT)
{
	ctxT.turtle->GetComponent<SpriteRenderer>()->SetTexture("Assets/Shell.png");
	ctxT.turtle->GetComponent<SquareCollider>()->SetSize(sf::Vector2f(40.f, 40.f));
	ctxT.turtle->GetComponent<VelocityComponent>()->SetX(0.f);
}

void ShellTurtle::Execute(TurtleContext& t, float dt)
{
	VelocityComponent* velocity = t.turtle->GetComponent<VelocityComponent>();
	if (IsHitByPlayer(t) && !isMoving) {
		float dir = t.player->GetTransform().scale.x;
		velocity->SetX(dir);
		isMoving = true;
	}

	if (velocity->GetVelocity().x == 0 && isMoving == true)
	{

		t.turtle->GetScene()->DeleteGameObject(t.turtle);

	}
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
