#pragma once
#include <Component.h>
#include "InteractableBlockType.h"

class InteractableBlockComponent : public Component
{

public:
	InteractableBlockComponent(InteractableBlockType type);

	// Récupère le type
	InteractableBlockType GetType();

	// Applique que le bloc est utilisé
	void SetUsed(bool isUsed);

	// Vérifie si le bloc est déjà utilisé
	bool IsUsed();

private:
	InteractableBlockType type;
	bool isUsed = false;

};