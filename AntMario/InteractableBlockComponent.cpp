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
	
	GameObject* bonusObject = owner->GetScene()->CreateGameObject("Bonus", { transform.pos.x , transform.pos.y - 48 });
	bonusObject->GetTransform().origin = sf::Vector2f(0.f, 0.f);
	bonusObject->AddComponent<SquareCollider>(sf::Vector2f(40.f, 40.f));
	
	switch (type) {
	case InteractableBlockType::FIRE_FLOWER:
		bonusObject->AddComponent<SpriteRenderer>("Assets/PowerUpSpriteSheet.png");
		bonusObject->GetComponent<SpriteRenderer>()->SetAnimationRule(SpriteAnimationRule(sf::Vector2i(0, 0), sf::Vector2i(40, 40), 3));
		bonusObject->AddComponent<BonusComponent>(BonusType::FIRE_FLOWER);

		break;
	case InteractableBlockType::MUSHROOM:
		bonusObject->AddComponent<SpriteRenderer>("Assets/PowerUpSpriteSheet.png");
		bonusObject->GetComponent<SpriteRenderer>()->SetAnimationRule(SpriteAnimationRule(sf::Vector2i(0, 0), sf::Vector2i(40, 40), 3));
		bonusObject->AddComponent<BonusComponent>(BonusType::MUSHROOM);
		break;
	case InteractableBlockType::COINS:
		bonusObject->AddComponent<SpriteRenderer>("Assets/Environment/Coins.png");
		bonusObject->AddComponent<BonusComponent>(BonusType::COINS);
		break;
	default:
		std::cout << "Not a bonus" << std::endl;
		break;
	}
}

