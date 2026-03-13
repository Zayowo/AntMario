#include "ResourceModule.h"
#include "Utils.h"

sf::Texture& ResourceModule::GetTexture(std::string path)
{

	if (!textureMap.contains(path)) {
		textureMap[path] = new sf::Texture(path);
		LogPrint("Texture created at `" + path + "`");
	}

	return *textureMap[path];

}

sf::Font& ResourceModule::GetFont(std::string path)
{

	if (!fontMap.contains(path))
	{
		fontMap[path] = new sf::Font(path);
		LogPrint("Font created at `" + path + "`");
	}

	return *fontMap[path];

}

sf::Sound& ResourceModule::GetSound(std::string path)
{

	if (!soundMap.contains(path))
	{
		sf::SoundBuffer* soundBuffer = new sf::SoundBuffer(path);
		soundMap[path] = new sf::Sound(*soundBuffer);
		LogPrint("Sound created at `" + path + "`");
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