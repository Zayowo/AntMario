#include "GameController.h"
#include <ResourceModule.h>
#include <iomanip>
#include <sstream>

void GameController::Init()
{
	ResourceModule* resourceModule = Engine::GetModule<ResourceModule>();
	sf::Font& font = resourceModule->GetFont("Assets/UI/Font.ttf");

	// Texte des pièces
	coinsText = new sf::Text(font, "", 24);
	coinsText->setFillColor(sf::Color::Yellow);
	coinsText->setPosition(sf::Vector2f(UI_OFFSET_X, UI_OFFSET_Y));

	// Texte des vies
	livesText = new sf::Text(font, "", 24);
	livesText->setFillColor(sf::Color::Red);
	livesText->setPosition(sf::Vector2f(UI_OFFSET_X, UI_OFFSET_Y + ELEMENT_SPACING));

	// Texte du chronomètre
	timerText = new sf::Text(font, "", 24);
	timerText->setFillColor(sf::Color::White);
	timerText->setPosition(sf::Vector2f(UI_OFFSET_X, UI_OFFSET_Y + ELEMENT_SPACING * 2));

	// Barre d'énergie - fond
	energyBarBackground.setSize(sf::Vector2f(ENERGY_BAR_WIDTH, ENERGY_BAR_HEIGHT));
	energyBarBackground.setFillColor(sf::Color::Black);
	energyBarBackground.setOutlineThickness(2.0f);
	energyBarBackground.setOutlineColor(sf::Color::White);
	energyBarBackground.setPosition(sf::Vector2f(UI_OFFSET_X, UI_OFFSET_Y + ELEMENT_SPACING * 3));

	// Barre d'énergie - valeur
	energyBar.setSize(sf::Vector2f(ENERGY_BAR_WIDTH, ENERGY_BAR_HEIGHT));
	energyBar.setFillColor(sf::Color::Green);
	energyBar.setPosition(sf::Vector2f(UI_OFFSET_X, UI_OFFSET_Y + ELEMENT_SPACING * 3));
}

void GameController::Update(float dt)
{
	// Mise à jour du texte des pièces
	coinsText->setString(std::to_string(coins));

	// Mise à jour du texte des vies
	livesText->setString(std::to_string(lives));

	// Mise à jour du chronomètre
	timerText->setString(std::to_string(totalTime));

	// Mise à jour de la barre d'énergie
	float energyPercent = (energy / maxEnergy);
	energyPercent = std::max(0.0f, std::min(1.0f, energyPercent)); // Clamp entre 0 et 1

	energyBar.setSize(sf::Vector2f(ENERGY_BAR_WIDTH * energyPercent, ENERGY_BAR_HEIGHT));

	// Changer la couleur de la barre selon le niveau d'énergie
	if (energyPercent > 0.5f) {
		energyBar.setFillColor(sf::Color::Green);
	}
	else if (energyPercent > 0.25f) {
		energyBar.setFillColor(sf::Color::Yellow);
	}
	else {
		energyBar.setFillColor(sf::Color::Red);
	}
}

void GameController::Render(sf::RenderWindow* window)
{
	// Sauvegarder la vue actuelle
	sf::View currentView = window->getView();

	// Utiliser la vue par défaut pour l'UI (coordonnées d'écran)
	window->setView(window->getDefaultView());

	// Dessiner les éléments du HUD
	window->draw(*coinsText);
	window->draw(*livesText);
	window->draw(*timerText);
	window->draw(energyBarBackground);
	window->draw(energyBar);

	// Restaurer la vue précédente
	window->setView(currentView);
}

void GameController::SetCoins(int newCoins)
{
	coins = newCoins;
}

void GameController::SetLives(int newLives)
{
	lives = newLives;
}

void GameController::SetEnergy(float newEnergy, float newMaxEnergy)
{
	energy = newEnergy;
	maxEnergy = newMaxEnergy;
}

void GameController::AddTime(float dt)
{
	totalTime += dt;
}

void GameController::ResetTime()
{
	totalTime = 0.0f;
}
