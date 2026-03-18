#pragma once
#include <Component.h>
#include <SFML/Graphics.hpp>

class GameController : public Component
{

public:
	void Init() override;
	void Update(float dt) override;
	void Render(sf::RenderWindow* window) override;

	// Setters pour mettre à jour les valeurs du HUD
	void SetCoins(int coins);
	void SetLives(int lives);
	void SetEnergy(float energy, float maxEnergy);
	void AddTime(float dt);
	void ResetTime();

	// Getters
	int GetCoins() const { return coins; }
	int GetLives() const { return lives; }
	float GetEnergy() const { return energy; }
	float GetTime() const { return totalTime; }

private:
	// Valeurs du HUD
	int coins = 0;
	int lives = 3;
	float energy = 0.0f;
	float maxEnergy = 100.0f;
	float totalTime = 0.0f;

	// Éléments graphiques
	sf::Font font;
	sf::Text* coinsText;
	sf::Text* livesText;
	sf::Text* timerText;
	sf::Text* fpsText;
	sf::RectangleShape energyBarBackground;
	sf::RectangleShape energyBar;

	// Positions et dimensions (UI sur le côté gauche)
	static constexpr float UI_OFFSET_X = 20.0f;
	static constexpr float UI_OFFSET_Y = 20.0f;
	static constexpr float ELEMENT_SPACING = 60.0f;
	static constexpr float ENERGY_BAR_WIDTH = 200.0f;
	static constexpr float ENERGY_BAR_HEIGHT = 20.0f;

	// Méthode pour formater le temps en MM:SS
	std::string FormatTime(float seconds);

};