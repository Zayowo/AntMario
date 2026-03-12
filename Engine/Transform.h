#pragma once
#include <SFML/System.hpp>
#include "Engine.h"
#include "WindowModule.h"

struct Transform
{

	sf::Vector2f pos = sf::Vector2f(0.f, 0.f);
	float rot = 0.f;
	sf::Vector2f scale = sf::Vector2f(1.f, 1.f);
	sf::Vector2f origin = sf::Vector2f(0.5f, 0.5f);

	// Récupère la vue du transform en fonction de la view
	sf::Vector2f GetViewRelativePos()
	{

		WindowModule* windowModule = Engine::GetModule<WindowModule>();
		sf::RenderWindow* window = windowModule->GetRenderWindow();
		return window->mapPixelToCoords(sf::Vector2i(pos), window->getView());

	};

};