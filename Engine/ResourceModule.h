#pragma once
#include <SFML/Graphics.hpp>
#include "Module.h"

class ResourceModule : public Module
{

public:
	// Récupère une texture
	// Si elle n'est pas trouvé, on crée une nouvelle texture à partir du path
	sf::Texture& GetTexture(std::string path);

	// Récupère une fonte
	// Si elle n'est pas trouvé, on crée une nouvelle font à partir du path
	sf::Font& GetFont(std::string path);

private:
	std::unordered_map<std::string, sf::Texture*> textureMap;
	std::unordered_map<std::string, sf::Font*> fontMap;

};