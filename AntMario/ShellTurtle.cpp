#include "ShellTurtle.h"
#include "SpriteRenderer.h"

void ShellTurtle::Enter(TurtleContext& ctxT)
{
	ctxT.turtle->GetComponent<SpriteRenderer>()->SetTexture("Assets/Shell.png");
}

void ShellTurtle::Execute(TurtleContext& t, float dt)
{
	//if jump ? direction depends on direction of maincharacter
}
