#include "ShellTurtle.h"
#include "SpriteRenderer.h"
#include "SquareCollider.h"
#include "VelocityComponent.h"
#include "Condition.h"
#include <Scene.h>
#include "GoombaComponent.h"
#include "TurtleComponent.h"
#include <Utils.h>
#include "PlayerController.h"

void ShellTurtle::Enter(TurtleContext& ctx)
{

	ctx.turtle->GetComponent<SquareCollider>()->SetSize(sf::Vector2f(40.f, 40.f));
	ctx.turtle->GetComponent<VelocityComponent>()->SetX(0.f);
	ctx.turtle->GetComponent<SpriteRenderer>()->SetAnimationRule(SpriteAnimationRule(sf::Vector2i(0, 30), sf::Vector2i(32, 32), 7));

	VelocityComponent* velocity = ctx.turtle->GetComponent<VelocityComponent>();

	velocity->RegisterHit("Goomba", VelocityHitType::LEFT, [this](GameObject* other) { DestroyGoomba(other); });
	velocity->RegisterHit("Goomba", VelocityHitType::RIGHT, [this](GameObject* other) { DestroyGoomba(other); });

	velocity->RegisterHit("Turtle", VelocityHitType::LEFT, [this](GameObject* other) { DestroyTurtle(other); });
	velocity->RegisterHit("Turtle", VelocityHitType::RIGHT, [this](GameObject* other) { DestroyTurtle(other); });

	velocity->RegisterHit("Player", VelocityHitType::LEFT, [this](GameObject* other) { if (isMoving) HitPlayer(other); });
	velocity->RegisterHit("Player", VelocityHitType::RIGHT, [this](GameObject* other) { if (isMoving) HitPlayer(other); });

}

void ShellTurtle::Execute(TurtleContext& ctx, float dt)
{

	Transform& transform = ctx.turtle->GetTransform();
	VelocityComponent* velocity = ctx.turtle->GetComponent<VelocityComponent>();
	float playerDir = ctx.player->GetTransform().scale.x;
	float turtleDir = ctx.turtle->GetTransform().scale.x;

	/*if (IsHitByPlayer(ctx))
	{
		std::cout << IsHitByPlayer(ctx) << std::endl;
		isMoving = !isMoving;
		ctx.turtle->GetTransform().scale.x = playerDir;
	}

	if (isMoving)
		velocity->SetX(turtleDir * 3.f);

	if (isMoving && velocity->GetVelocity().x == 0.f)
	{
		ctx.player->GetTransform().scale.x = -turtleDir;
		velocity->SetX(turtleDir * 3.f);
	}*/

	bool hitByPlayer = IsHitByPlayer(ctx);
	if (hitByPlayer && !isMoving) {
		velocity->SetX(std::round(playerDir) * 3);
		isMoving = true;
	} else if (hitByPlayer && isMoving) {
		velocity->SetX(0.f);
		isMoving = false;
	}

	if (velocity->GetVelocity().x == 0 && isMoving == true)
	{
		LogPrint("Si j'ai touché un ennemi, c'est pas censé le faire!!");
		velocity->SetX(-turtleDir * 3);
		// ctx.turtle->GetScene()->DeleteGameObject(ctx.turtle);
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

void ShellTurtle::DestroyGoomba(GameObject* other) {
	GoombaComponent* GComponent = other->GetComponent<GoombaComponent>();
	if (GComponent == nullptr)
		std::cerr << "Error : in ShellTurtle missing GoombaComponent" << std::endl;
	
	if (isMoving)
		GComponent->Kill();
}

void ShellTurtle::DestroyTurtle(GameObject* other) {
	TurtleComponent* TComponent = other->GetComponent<TurtleComponent>();
	if (TComponent == nullptr)
		std::cerr << "Error : in ShellTurtle missing TurtleComponent" << std::endl;

	if (isMoving)
		TComponent->Kill();
}

void ShellTurtle::HitPlayer(GameObject* other) {
	PlayerController* playerController = other->GetComponent<PlayerController>();
	if (playerController == nullptr)
	{
		std::cerr << "Error : in ShellTurtle missing PlayerController" << std::endl;
		return;
	}

	playerController->HitByEnemy(other);
}
