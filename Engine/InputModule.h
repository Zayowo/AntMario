#pragma once
#include <SFML/Graphics.hpp>
#include "Module.h"
#include "InputInfo.h"

class InputModule : public Module
{

public:
	void Update() override;

	// Enregistre un(e) key/button dont l'état sera vérifié dans l'Update
	void RegisterInput(sf::Keyboard::Key key);
	void RegisterInput(sf::Mouse::Button button);

	// Vérifie si l'input est cliqué / pressé / relaché
	// Voir "InputInfo.h" pour les différents états possible :)
	bool Is(sf::Keyboard::Key key, InputState state);
	bool Is(sf::Mouse::Button button, InputState state);

	// Récupère la state d'un input depuis son info
	InputState GetState(InputInfo info);

private:
	std::unordered_map<sf::Keyboard::Key, InputInfo> keyInfoMap;
	std::unordered_map<sf::Mouse::Button, InputInfo> buttonInfoMap;

};