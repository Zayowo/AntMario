#include <SpriteRenderer.h>
#include "InteractableBlockComponent.h"

InteractableBlockComponent::InteractableBlockComponent(InteractableBlockType type) :
	type(type)
{};

InteractableBlockType InteractableBlockComponent::GetType()
{

	return type;

}

void InteractableBlockComponent::SetUsed(bool isUsed)
{

	this->isUsed = isUsed;

	SpriteRenderer* sprite = owner->GetComponent<SpriteRenderer>();

	if (!sprite)
		return;

	sprite->SetTexture("Assets/Environment/LuckyBlock_Used.png");

}

bool InteractableBlockComponent::IsUsed()
{

	return isUsed;

}