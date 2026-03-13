#include "Bonus.h"
#include "iostream"


sf::Color Bonus::getColorForType(BonusType type)
{
    switch (type)
    {
    case BonusType ::COINS:
        return sf::Color(255, 255, 0);     // Yellow
    case BonusType::Bonus1:
        return sf::Color(100, 200, 255);  // Bleu clair
    case BonusType::Bonus2:
        return sf::Color(128, 0, 128);   // Purple
    case BonusType::Bonus3:
        return sf::Color(255, 100, 100);  // Rouge clair
    default:
        return sf::Color::White;
    }
}

Bonus::Bonus(BonusType type)
{
    shape.setRadius(20.0f);
    shape.setOrigin({ 20.0f, 20.0f });  // Centrer l'origine 

    // Définir la couleur selon le type
    shape.setFillColor(getColorForType(type));

    // Ajouter un contour blanc pour meilleure visibilité
    shape.setOutlineColor(sf::Color::White);
    shape.setOutlineThickness(3.0f);

    shape.setPosition({ x, y });

    std::cout << "Bonus créé! Type: " << static_cast<int>(type) << std::endl;
}

void Bonus::Update(float dt)
{

    shape.setPosition(owner->GetTransform().pos);

}

void Bonus::Render(sf::RenderWindow* window)
{
    window->draw(shape);
}

sf::Vector2f Bonus::getPosition() const
{
    return { x, y };
}

sf::FloatRect Bonus::getBounds() const
{
    return shape.getGlobalBounds();
}

sf::FloatRect Bonus::getHitbox() const
{
    // Pour les bonus, on garde une hitbox généreuse (90% de la taille)
    sf::FloatRect bounds = shape.getGlobalBounds();

    float reductionFactor = 0.9f;
    float widthReduction = bounds.size.x * (1.0f - reductionFactor) / 2.0f;
    float heightReduction = bounds.size.y * (1.0f - reductionFactor) / 2.0f;

    return sf::FloatRect(
        { bounds.position.x + widthReduction, bounds.position.y + heightReduction },
        { bounds.size.x * reductionFactor, bounds.size.y * reductionFactor }
    );
}

