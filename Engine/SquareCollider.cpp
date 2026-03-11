#include "SquareCollider.h"
#include "Scene.h"

SquareCollider::SquareCollider(sf::Vector2f size)
{

	shape = new sf::RectangleShape(size);
	shape->setFillColor(sf::Color::Transparent);
	shape->setOutlineColor(sf::Color::Red);
	shape->setOutlineThickness(-2.f);

};

void SquareCollider::Init()
{

	Transform& transform = owner->GetTransform();
	shape->setPosition(transform.pos);
	shape->setRotation(sf::degrees(transform.rot));
	shape->setScale(transform.scale);
	shape->setOrigin(sf::Vector2f(
		shape->getLocalBounds().size.x * transform.origin.x,
		shape->getLocalBounds().size.y * transform.origin.y
	));

}

void SquareCollider::Update(float dt)
{

	// Nan mais, logique.
	if (collisionCallbackMap.empty())
		return;

	Scene* scene = owner->GetScene();
	
	if (!scene)
		return;

	for (auto [name, callbacks] : collisionCallbackMap)
	{

		std::vector<GameObject*> gameObjects = scene->GetGameObjectsByName(name);

		for (GameObject* gameObject : gameObjects)
		{

			if (IsColliding(gameObject))
			{

				for (std::function<void(GameObject*)> callback : callbacks)
					callback(gameObject);

			}

		}

	}

}

void SquareCollider::Render(sf::RenderWindow* window)
{

	Transform& transform = owner->GetTransform();
	shape->setPosition(transform.pos);
	shape->setRotation(sf::degrees(transform.rot));
	shape->setScale(transform.scale);
	shape->setOrigin(sf::Vector2f(
		shape->getLocalBounds().size.x * transform.origin.x,
		shape->getLocalBounds().size.y * transform.origin.y
	));

	window->draw(*shape);

}

bool SquareCollider::IsColliding(GameObject* gameObject)
{

	SquareCollider* bCollider = gameObject->GetComponent<SquareCollider>();

	if (!bCollider)
		return false;

	// Détéction de collisions en AABB
	sf::FloatRect aBounds = shape->getGlobalBounds();
	sf::FloatRect bBounds = bCollider->shape->getGlobalBounds();

	if (aBounds.findIntersection(bBounds))
		return true;

	return false;

}

void SquareCollider::RegisterCollisionCallback(std::string name, std::function<void(GameObject*)> callback)
{

	collisionCallbackMap[name].emplace_back(callback);

}