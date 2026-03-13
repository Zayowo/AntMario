#include "Oppenent.h"
#include <iostream>

Oppenent::Oppenent(float startX, float startY, OppenenType type)
    : x(startX), y(startY), type(type), currentFrame(0), moveTimer(0.0f)
{
    // Définir la santé selon le type d'ennemi
    switch (type)
    {
    case OppenenType::oppenent1:
        health = 1;
        break;
    case OppenenType::oppenent2:
        health = 2;
        break;
    case OppenenType::oppenent3:
        health = 1;
        break;
    }
}

void Oppenent::update(float oppenentX, float oppenentY)
{
    switch (type)
    {
    case OppenenType::oppenent1: // FACILE - SUIVI SIMPLE
    {
        float speed = 0.5f;
        x -= speed; // Se déplace uniquement vers la gauche
        break;
    }
}
