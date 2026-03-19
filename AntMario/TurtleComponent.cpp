#include "TurtleComponent.h"
#include <VelocityComponent.h>
#include <SquareCollider.h>
#include <Scene.h>
#include "FSMComponent.h"
#include "TurtleContext.h"
//#include "InitialTurtle.h"
//#include "ShellTurtle.h"
//#include "Condition.h"

void TurtleComponent::Init()
{
	EnemyComponent::Init();
	/*FSMComponent<TurtleContext>* fsmTurtle = owner->GetComponent<FSMComponent<TurtleContext>>();

	InitialTurtle* initTurtle = fsmTurtle->CreateState<InitialTurtle>();
	ShellTurtle* shellTurtle = fsmTurtle->CreateState<ShellTurtle>();

	initTurtle->AddTransition(Condition::IsHitByPlayer, shellTurtle);

	fsmTurtle->Init(initTurtle);*/

	VelocityComponent* velocity = owner->GetComponent<VelocityComponent>();

	velocity->RegisterHit("Terrain", VelocityHitType::LEFT, [this](GameObject* other) { ChangeDirection(-1); });
	velocity->RegisterHit("Terrain", VelocityHitType::RIGHT, [this](GameObject* other) { ChangeDirection(1); });

}

void TurtleComponent::Update(float dt)
{
	FSMComponent<TurtleContext>* fsm = owner->GetComponent<FSMComponent<TurtleContext>>();

	if (fsm == nullptr)
		std::cerr << "TurtleComponent : missing FSMComponent<TurtleContext>";
	
	fsm->Update(dt);
}

void TurtleComponent::StepByPlayer(GameObject* other)
{
	VelocityComponent* otherVelocityComponent = other->GetComponent<VelocityComponent>();
	otherVelocityComponent->SetY(-350.f);
	owner->GetScene()->DeleteGameObject(owner);

}

void TurtleComponent::ChangeDirection(float dir) {

	owner->GetComponent<FSMComponent<TurtleContext>>()->GetContext().direction = dir;

}
