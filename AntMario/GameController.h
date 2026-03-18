#pragma once
#include <Component.h>
#include <SFML/Graphics.hpp>
#include "GameStateManager.h"

class GameController : public Component
{

public:
	GameController();
	void Init() override;
	void Update(float dt) override;
	void Render(sf::RenderWindow* window) override;

	// Récupère la référence de la quantité de pièces, on peut la modifier
	int* GetCoins();

	// Récupère l'énergie du joueur, on peut la modifier
	float* GetEnergy();

private:
	int* coins;
	float* energy;
	
	// Éléments de l'UI
	sf::Sprite* coinsIcon;
	sf::Sprite* livesIcon;
	sf::Sprite* energyIcon;
	sf::Text* coinsText;
	sf::Text* livesText;
	sf::RectangleShape energyBarBackground;
	sf::RectangleShape energyBar;

};