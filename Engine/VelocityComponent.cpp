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

	collider->RegisterCallback("Collider", [this](GameObject* other) { ResolveCollisions(other); });
    collider->RegisterCallback("Brick", [this](GameObject* other) { ResolveCollisions(other); });

}

void VelocityComponent::Update(float dt)
{

	velocity.y += 1950.f * dt;

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

void VelocityComponent::AddX(float x)
{

    velocity.x += x;

}

void VelocityComponent::AddY(float y)
{

    velocity.y += y;

}

sf::Vector2f VelocityComponent::GetVelocity()
{

    return velocity;

}

void VelocityComponent::RegisterHit(std::string name, VelocityHitType hitType, std::function<void(GameObject*)> callback)
{

    hitCallbackMap[name][hitType].push_back(callback);

}

void VelocityComponent::ResolveCollisions(GameObject* other) {

    if (!other) return;

    auto collider = owner->GetComponent<SquareCollider>();
    auto otherCollider = other->GetComponent<SquareCollider>();

    if (!collider || !otherCollider) return;


    sf::FloatRect playerBounds = collider->GetBounds();
    sf::FloatRect otherBounds = otherCollider->GetBounds();

    // Calcul de l'intersection
    sf::FloatRect intersection;
    if (playerBounds.findIntersection(otherBounds))
        intersection = *playerBounds.findIntersection(otherBounds);
    else
        return;

    Transform& transform = owner->GetTransform();

    // Déterminer l'axe de collision dominant
    // Si la largeur de l'intersection est plus petite que sa hauteur, c'est une collision horizontale
    if (intersection.size.x < intersection.size.y) {

        if (playerBounds.position.x < otherBounds.position.x)
        {

            transform.pos.x = otherBounds.position.x - (playerBounds.size.x * (1.0f - transform.origin.x)) - 0.01f;
            SendHit(other, VelocityHitType::LEFT);

        }
        else
        {

            transform.pos.x = otherBounds.position.x + otherBounds.size.x + (playerBounds.size.x * transform.origin.x) + 0.01f;
            SendHit(other, VelocityHitType::RIGHT);

        }
        velocity.x = 0.f;

    }
    else
    {
        if (playerBounds.position.y < otherBounds.position.y)
        {

            transform.pos.y = otherBounds.position.y - (playerBounds.size.y * (1.0f - transform.origin.y)) - 0.01f;
            if (velocity.y > 0) velocity.y = 0.f;
            SendHit(other, VelocityHitType::TOP);

        }
        else
        {

            transform.pos.y = otherBounds.position.y + otherBounds.size.y + (playerBounds.size.y * transform.origin.y) + 0.01f;
            float _velocityY = velocity.y;
            if (velocity.y < 0) velocity.y = 0.01f;
            
            if (_velocityY < 0.f)
                SendHit(other, VelocityHitType::BOTTOM);

        }

    }

}

void VelocityComponent::SendHit(GameObject* other, VelocityHitType hitType)
{

	for (auto callback : hitCallbackMap[other->GetName()][hitType])
        callback(other);

}