#pragma once
#include <SFML/Graphics.hpp>

class GameObject;

// Variables statiques
static sf::RenderWindow* ref_renderWindow = nullptr;

// Permet de savoir si l'objet est dans la range de caméra
// En gros si elle doit être chargé ou non :)
bool IsLoaded(GameObject* gameObject);