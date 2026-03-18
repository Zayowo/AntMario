#include "ShellTurtle.h"
#include "SpriteRenderer.h"
#include "SquareCollider.h"

void ShellTurtle::Enter(TurtleContext& ctxT)
{
	ctxT.turtle->GetComponent<SpriteRenderer>()->SetTexture("Assets/Shell.png");
	ctxT.turtle->GetComponent<SquareCollider>()->SetSize(sf::Vector2f(40.f, 40.f));
}

void ShellTurtle::Execute(TurtleContext& t, float dt)
{
	//if jump ? direction depends on direction of maincharacter
}
