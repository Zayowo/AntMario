
#include "ResourceModule.h"

sf::Texture& ResourceModule::GetTexture(std::string path)
{

	if (!textureMap.contains(path)) {
		textureMap[path] = new sf::Texture(path);
		std::cout << "Texture created at `" + path + "`" << std::endl;
	}

	return *textureMap[path];

}

sf::Font& ResourceModule::GetFont(std::string path)
{

	if (!fontMap.contains(path))
		fontMap[path] = new sf::Font(path);

	return *fontMap[path];

}