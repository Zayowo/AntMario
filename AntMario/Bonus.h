#pragma once
#include <Component.h>
#include <SFML/Graphics.hpp>
#include <vector>

enum class BonusType
{
	Coins, //Pièces à collectionner
	Bonus1, //Bonus qui rend le joueur invincible sur un coup
	Bonus2, //Bonus qui rend le joueur grand  
	Bonus3 //Bonus permettant au joueur de lancer des projectiles

};

class Bonus : public Component
{
private:
    float x, y;
    float speed;
    BonusType type;
    sf::CircleShape shape;

    // Animation (pulsation)
    sf::Clock pulseTimer;
    float pulseScale;

    // Couleurs statiques pour chaque type
    static sf::Color getColorForType(BonusType type);

public:
    Bonus(BonusType type);

    void Update(float dt) override;
    void Render(sf::RenderWindow* window) override;

    sf::Vector2f getPosition() const;
    sf::FloatRect getBounds() const;
    sf::FloatRect getHitbox() const;
    BonusType getType() const { return type; }
};

