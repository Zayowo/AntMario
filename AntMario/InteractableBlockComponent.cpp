#include <SpriteRenderer.h>
#include <SquareCollider.h>
#include "InteractableBlockComponent.h"
#include "Scene.h"
#include "BonusComponent.h"

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

	SpawnContent();


}

bool InteractableBlockComponent::IsUsed()
{

	return isUsed;

}

void InteractableBlockComponent::SpawnContent() {
	Transform& transform = owner->GetTransform();
	
	GameObject* bonusObject;
	
	switch (type) {
	case InteractableBlockType::FIRE_FLOWER:
		bonusObject = owner->GetScene()->CreateGameObject("Bonus", { transform.pos.x , transform.pos.y - 48 });
		bonusObject->GetTransform().origin = sf::Vector2f(0.f, 0.f);
		bonusObject->AddComponent<SpriteRenderer>("Assets/FireFlower.png");
		bonusObject->AddComponent<BonusComponent>(BonusType::FIRE_FLOWER);
		bonusObject->AddComponent<SquareCollider>(sf::Vector2f(40.f, 40.f));

		break;
	case InteractableBlockType::MUSHROOM:
		bonusObject = owner->GetScene()->CreateGameObject("Bonus", { transform.pos.x , transform.pos.y - 48 });
		bonusObject->GetTransform().origin = sf::Vector2f(0.f, 0.f);
		bonusObject->AddComponent<SpriteRenderer>("Assets/Mushroom.png");
		bonusObject->AddComponent<BonusComponent>(BonusType::MUSHROOM);
		bonusObject->AddComponent<SquareCollider>(sf::Vector2f(40.f, 40.f));
		break;
	case InteractableBlockType::COINS:
		bonusObject = owner->GetScene()->CreateGameObject("Bonus", { transform.pos.x , transform.pos.y - 48 });
		bonusObject->GetTransform().origin = sf::Vector2f(0.f, 0.f);
		bonusObject->AddComponent<SpriteRenderer>("Assets/Environment/Coins.png");
		bonusObject->AddComponent<BonusComponent>(BonusType::COINS);
		bonusObject->AddComponent<SquareCollider>(sf::Vector2f(40.f, 40.f));
		break;
	default:
		std::cout << "Not a bonus" << std::endl;
		break;
	}
}

