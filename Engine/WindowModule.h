#pragma once
#include <SFML/Graphics.hpp>
#include "Module.h"

class WindowModule : public Module
{
public:
	void Init() override;
	void Update() override;
	void Render() override;

	// Récupère la render window du module
	sf::RenderWindow* GetRenderWindow();

private:
	sf::RenderWindow* window;
};