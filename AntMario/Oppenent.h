#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include <optional>

enum class OppenenType
{
    oppenent1, // Copie du champignon
    oppenent2, // Copie de la tortue
    oppenent3 // Copie du piranha
};

class Oppenent {
private:
    float x, y;
    OppenenType type;
    std::optional<sf::Sprite> sprite;
    int health;  // Points de vie de l'ennemi

    // Animation
    int currentFrame;
    sf::Clock animationClock;

    // Comportement
    sf::Clock shootClock;
    float moveTimer;

public:
    Oppenent(float startX, float startY, OppenenType type);

    void update(float oppenentX, float oppenentY);
    void draw(sf::RenderWindow& window);

    sf::Vector2f getPosition() const;
    sf::FloatRect getBounds() const;
    sf::FloatRect getHitbox() const;  // Hitbox r?duite pour collision pr?cise
    OppenenType getType() const;

    // Gestion de la sant?
    int getHealth() const { return health; }
    void takeDamage(int damage);
    bool isAlive() const { return health > 0; }

    // M?thode publique pour charger les textures
    static void loadTextures();
};