#include "GameController.h"
#include <ResourceModule.h>
#include <TimeModule.h>
#include <iomanip>
#include <sstream>

GameController::GameController() :
	energyBarBackground(sf::Vector2f(175.f, 20.f)),
	energyBar(sf::Vector2f(175.f, 20.f))
{
	
	coins = new int(0);
	energy = new float(0.f);

	energyBarBackground.setFillColor(sf::Color(40, 40, 40, 150));
	energyBar.setFillColor(sf::Color(140, 0, 180));
	energyBarBackground.setPosition(sf::Vector2f(100.f, 115.f));
	energyBar.setPosition(sf::Vector2f(100.f, 115.f));

};

void GameController::Init()
{

	ResourceModule* resourceModule = Engine::GetModule<ResourceModule>();
	sf::Font& font = resourceModule->GetFont("Assets/UI/Font.ttf");

	coinsIcon = new sf::Sprite(resourceModule->GetTexture("Assets/UI/T_UI_Coins.png"));
	coinsText = new sf::Text(font, "x0", 24);
	coinsIcon->setPosition(sf::Vector2f(60.f, 20.f));
	coinsText->setPosition(sf::Vector2f(100.f, 20.f));

	livesIcon = new sf::Sprite(resourceModule->GetTexture("Assets/UI/T_UI_Lives.png"));
	livesText = new sf::Text(font, "x0", 24);
	livesIcon->setPosition(sf::Vector2f(60.f, 65.f));
	livesText->setPosition(sf::Vector2f(100.f, 65.f));

	energyIcon = new sf::Sprite(resourceModule->GetTexture("Assets/UI/T_UI_Energy.png"));
	energyIcon->setPosition(sf::Vector2f(60.f, 110.f));

}

void GameController::Update(float dt)
{

	if (*energy > 1.f)
		*energy = 1.f;

	coinsText->setString("x" + std::to_string(*coins));
	livesText->setString(std::string("x") + std::to_string(GameStateManager::GetLives()));
	energyBar.setSize(sf::Vector2f(175.f * (*energy), 20.f));

}
	
void GameController::Render(sf::RenderWindow* window)
{

	const sf::View currentView = window->getView();
	sf::View newView = window->getDefaultView();
	newView.rotate(sf::degrees(5.f));

	window->setView(newView);

	window->draw(*coinsIcon);
	window->draw(*coinsText);
	window->draw(*livesIcon);
	window->draw(*livesText);
	window->draw(*energyIcon);
	window->draw(energyBarBackground);
	window->draw(energyBar);

	window->setView(currentView);

}

int* GameController::GetCoins()
{
	
	return coins;

}

float* GameController::GetEnergy()
{

	return energy;

}

//	// Texte des pièces
//	coinsText = new sf::Text(font, "", 24);
//	coinsText->setFillColor(sf::Color::Yellow);
//	coinsText->setPosition(sf::Vector2f(UI_OFFSET_X, UI_OFFSET_Y));
//
//	// Texte des vies
//	livesText = new sf::Text(font, "", 24);
//	//livesText->setFillColor(sf::Color::Red);
//	//livesText->setPosition(sf::Vector2f(UI_OFFSET_X, UI_OFFSET_Y + ELEMENT_SPACING));
//
//	// Texte du chronomètre
//	timerText = new sf::Text(font, "", 24);
//	//timerText->setFillColor(sf::Color::White);
//	//timerText->setPosition(sf::Vector2f(UI_OFFSET_X, UI_OFFSET_Y + ELEMENT_SPACING * 2));
//
//	fpsText = new sf::Text(font, "", 24);
//	fpsText->setPosition(sf::Vector2f(UI_OFFSET_X, UI_OFFSET_Y + ELEMENT_SPACING * 2));
//
//	// Barre d'énergie - fond
//	energyBarBackground.setSize(sf::Vector2f(ENERGY_BAR_WIDTH, ENERGY_BAR_HEIGHT));
//	energyBarBackground.setFillColor(sf::Color::Black);
//	energyBarBackground.setOutlineThickness(2.0f);
//	energyBarBackground.setOutlineColor(sf::Color::White);
//	energyBarBackground.setPosition(sf::Vector2f(UI_OFFSET_X, UI_OFFSET_Y + ELEMENT_SPACING));
//
//	// Barre d'énergie - valeur
//	energyBar.setSize(sf::Vector2f(ENERGY_BAR_WIDTH, ENERGY_BAR_HEIGHT));
//	energyBar.setFillColor(sf::Color::Green);
//	energyBar.setPosition(sf::Vector2f(UI_OFFSET_X, UI_OFFSET_Y + ELEMENT_SPACING ));
//}
//
//void GameController::Update(float dt)
//{
//	// Mise à jour du texte des pièces
//	coinsText->setString(std::to_string(coins));
//
//	// Mise à jour du texte des vies
//	livesText->setString(std::to_string(lives));
//
//	// Mise à jour du chronomètre
//	timerText->setString(std::to_string(totalTime));
//
//	fpsText->setString("FPS " + std::to_string((int)(1.0f / Engine::GetModule<TimeModule>()->GetDeltaTime())));
//
//	// Mise à jour de la barre d'énergie
//	float energyPercent = (energy / maxEnergy);
//	energyPercent = std::max(0.0f, std::min(1.0f, energyPercent)); // Clamp entre 0 et 1
//
//	energyBar.setSize(sf::Vector2f(ENERGY_BAR_WIDTH * energyPercent, ENERGY_BAR_HEIGHT));
//
//	// Changer la couleur de la barre selon le niveau d'énergie
//	if (energyPercent > 0.5f) {
//		energyBar.setFillColor(sf::Color::Green);
//	}
//	else if (energyPercent > 0.25f) {
//		energyBar.setFillColor(sf::Color::Yellow);
//	}
//	else {
//		energyBar.setFillColor(sf::Color::Red);
//	}
//}
//
//void GameController::Render(sf::RenderWindow* window)
//{
//	// Sauvegarder la vue actuelle
//	sf::View currentView = window->getView();
//
//	// Utiliser la vue par défaut pour l'UI (coordonnées d'écran)
//	window->setView(window->getDefaultView());
//
//	// Dessiner les éléments du HUD
//	window->draw(*coinsText);
//	//window->draw(*livesText);
//	//window->draw(*timerText);
//	window->draw(energyBarBackground);
//	window->draw(energyBar);
//	window->draw(*fpsText);
//
//	// Restaurer la vue précédente
//	window->setView(currentView);
//}
//
//void GameController::SetCoins(int newCoins)
//{
//	coins = newCoins;
//}
//
//void GameController::SetLives(int newLives)
//{
//	lives = newLives;
//}
//
//void GameController::SetEnergy(float newEnergy, float newMaxEnergy)
//{
//	energy = newEnergy;
//	maxEnergy = newMaxEnergy;
//}
//
//void GameController::AddTime(float dt)
//{
//	totalTime += dt;
//}
//
//void GameController::ResetTime()
//{
//	totalTime = 0.0f;
//}