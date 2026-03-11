#include "VelocityComponent.h"
#include "SquareCollider.h"

VelocityComponent::VelocityComponent(float speed) :
	speed(speed)
{};

void VelocityComponent::Init()
{

	SquareCollider* collider = owner->GetComponent<SquareCollider>();

	if (!collider)
		return;

	collider->RegisterCollisionCallback("Collider", [this](GameObject* other) { ResolveCollisions(other); });

}

void VelocityComponent::Update(float dt)
{

	velocity.y += 1600.f * dt;

	Transform& transform = owner->GetTransform();
	transform.pos.x += velocity.x * speed * dt;
    transform.pos.y += velocity.y * dt;

}

void VelocityComponent::SetVelocity(sf::Vector2f velocity)
{

	this->velocity = velocity;

}

void VelocityComponent::SetX(float x)
{

	velocity.x = x;

}

void VelocityComponent::SetY(float y)
{

	velocity.y = y;

}

sf::Vector2f VelocityComponent::GetVelocity()
{

    return velocity;

}

void VelocityComponent::ResolveCollisions(GameObject* other)
{
    if (!other)
        return;

    auto collider = owner->GetComponent<SquareCollider>();
    auto otherCollider = other->GetComponent<SquareCollider>();

    if (!collider || !otherCollider)
        return;

    Transform& transform = owner->GetTransform();

    // Récupérer les bounds en espace GLOBAL (position transformée)
    sf::FloatRect playerBounds = collider->GetBounds();
    sf::FloatRect otherBounds = otherCollider->GetBounds();

    // Calculer les chevauchements
    float overlapLeft = (playerBounds.position.x + playerBounds.size.x) - otherBounds.position.x;
    float overlapRight = (otherBounds.position.x + otherBounds.size.x) - playerBounds.position.x;
    float overlapTop = (playerBounds.position.y + playerBounds.size.y) - otherBounds.position.y;
    float overlapBottom = (otherBounds.position.y + otherBounds.size.y) - playerBounds.position.y;

    // Trouver le chevauchement minimum
    float minOverlap = std::min({ overlapLeft, overlapRight, overlapTop, overlapBottom });

    // Appliquer la correction en tenant compte de l'origin
    if (minOverlap == overlapTop && velocity.y > 0.f)
    {
        // Collision par le haut (le joueur tombe sur un objet)
        float correction = otherBounds.position.y - playerBounds.size.y;
        transform.pos.y = correction + (playerBounds.size.y * transform.origin.y);
        velocity.y = 0.f;
    }
    else if (minOverlap == overlapBottom && velocity.y < 0.f)
    {
        // Collision par le bas (le joueur saute contre quelque chose)
        float correction = otherBounds.position.y + otherBounds.size.y;
        transform.pos.y = correction - (playerBounds.size.y * (transform.origin.y));
        velocity.y = 0.f;
    }
    else if (minOverlap == overlapLeft && velocity.x > 0.f)
    {
        // Collision par la gauche
        float correction = otherBounds.position.x - playerBounds.size.x;
        transform.pos.x = correction + (playerBounds.size.x * transform.origin.x);
        velocity.x = 0.f;
    }
    else if (minOverlap == overlapRight && velocity.x < 0.f)
    {
        // Collision par la droite
        float correction = otherBounds.position.x + otherBounds.size.x;
        transform.pos.x = correction - (playerBounds.size.x * (transform.origin.x));
        velocity.x = 0.f;
    }
}