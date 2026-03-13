#include "TilemapRenderer.h"
#include "ResourceModule.h"
#include "Engine.h"

TilemapRenderer::TilemapRenderer(std::string texturePath, sf::Vector2u tileSize, unsigned int width, unsigned int height)
    : m_tileSize(tileSize), m_width(width), m_height(height)
{
    // Récupération de la texture via le ResourceModule
    ResourceModule* res = Engine::GetModule<ResourceModule>();
    m_tileset = new sf::Texture(res->GetTexture(texturePath));
    
    m_vertices.setPrimitiveType(sf::PrimitiveType::Triangles);
    // On initialise le VertexArray à la taille maximale du niveau (6 sommets par tuile)
    m_vertices.resize(width * height * 6);

    // On initialise toutes les positions à zéro ou hors champ au début
    for (unsigned int i = 0; i < m_vertices.getVertexCount(); ++i)
        m_vertices[i].position = sf::Vector2f(-1000.f, -1000.f);
}

void TilemapRenderer::SetTile(unsigned int x, unsigned int y, sf::Vector2i uvPos)
{
    if (x >= m_width || y >= m_height) return;

    // Index de départ pour les 6 sommets de la tuile (x, y)
    unsigned int index = (x + y * m_width) * 6;
    sf::Vertex* tri = &m_vertices[index];

    float tw = (float)m_tileSize.x;
    float th = (float)m_tileSize.y;

    // Positions des coins dans le monde
    sf::Vector2f p0(x * tw, y * th);
    sf::Vector2f p1((x + 1) * tw, y * th);
    sf::Vector2f p2((x + 1) * tw, (y + 1) * th);
    sf::Vector2f p3(x * tw, (y + 1) * th);

    // Coordonnées de texture (UV)
    sf::Vector2f t0((float)uvPos.x, (float)uvPos.y);
    sf::Vector2f t1((float)uvPos.x + tw, (float)uvPos.y);
    sf::Vector2f t2((float)uvPos.x + tw, (float)uvPos.y + th);
    sf::Vector2f t3((float)uvPos.x, (float)uvPos.y + th);

    // Triangle 1
    tri[0].position = p0; tri[0].texCoords = t0;
    tri[1].position = p1; tri[1].texCoords = t1;
    tri[2].position = p2; tri[2].texCoords = t2;

    // Triangle 2
    tri[3].position = p0; tri[3].texCoords = t0;
    tri[4].position = p2; tri[4].texCoords = t2;
    tri[5].position = p3; tri[5].texCoords = t3;
}

void TilemapRenderer::Render(sf::RenderWindow* window)
{
    sf::RenderStates states;
    // On applique la transformation du GameObject parent si nécessaire
    // states.transform *= owner->GetTransform().getTransform(); 
    states.texture = m_tileset;
    window->draw(m_vertices, states);
}