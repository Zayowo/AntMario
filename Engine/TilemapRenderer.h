#pragma once
#include <SFML/Graphics.hpp>
#include "Component.h"

class TilemapRenderer : public Component
{
public:
    TilemapRenderer(std::string texturePath, sf::Vector2u tileSize, unsigned int width, unsigned int height);

    void Render(sf::RenderWindow* window) override;
    
    // Modifie une tuile spécifique dans le VertexArray
    void SetTile(unsigned int x, unsigned int y, sf::Vector2i uvPos);


private:
    sf::VertexArray m_vertices;
    sf::Texture* m_tileset;
    sf::Vector2u m_tileSize;
    unsigned int m_width;
    unsigned int m_height;
};