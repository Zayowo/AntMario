#include <ResourceModule.h>
#include <Scene.h>
#include <SquareCollider.h>
#include "BonusComponent.h"

BonusComponent::BonusComponent(BonusType type) :
	type(type)
{};

BonusType BonusComponent::GetType()
{

	return type;

}