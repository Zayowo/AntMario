#pragma once
#include <Component.h>
#include "BonusType.h"

class BonusComponent : public Component
{

public:
	BonusComponent(BonusType type);

	// Récupère le type
	BonusType GetType();

private:
	BonusType type;

};