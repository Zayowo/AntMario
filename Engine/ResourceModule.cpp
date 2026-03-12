
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

sf::Sound& ResourceModule::GetSound(std::string path)
{

	if (!soundMap.contains(path))
	{
		sf::SoundBuffer* soundBuffer = new sf::SoundBuffer(path);
		soundMap[path] = new sf::Sound(*soundBuffer);
		std::cout << "Sound created at `" + path + "`" << std::endl;
	}

	return *soundMap[path];

}

void ResourceModule::PlaySound(std::string path, float volume, float pitch)
{

	if (!soundMap.contains(path))
		GetSound(path);
	
	soundMap[path]->setVolume(volume);
	soundMap[path]->setPitch(pitch);
	soundMap[path]->play();

}