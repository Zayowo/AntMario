#include "ShellTurtle.h"
#include "SpriteRenderer.h"
#include "SquareCollider.h"
#include "VelocityComponent.h"

void ShellTurtle::Enter(TurtleContext& ctxT)
{
	ctxT.turtle->GetComponent<SpriteRenderer>()->SetTexture("Assets/Shell.png");
	ctxT.turtle->GetComponent<SquareCollider>()->SetSize(sf::Vector2f(40.f, 40.f));
	ctxT.turtle->GetComponent<VelocityComponent>()->SetX(0.f);
}

void ShellTurtle::Execute(TurtleContext& t, float dt)
{
	//if jump ? direction depends on direction of maincharacter
}
