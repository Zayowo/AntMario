#pragma once
#include <Component.h>

class BackgroundElement : public Component
{

public:
	BackgroundElement(std::string path, float depth, sf::Vector2f offset);

	void Init();
	void Update(float dt);
	void Render(sf::RenderWindow* window);

private:
	sf::Sprite* sprite;
	float depth;
	sf::Vector2f offset;
	GameObject* player;

};