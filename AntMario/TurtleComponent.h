#pragma once
#include "EnemyComponent.h"
class TurtleComponent : public EnemyComponent
{
	void Init() override;
	void Update(float dt) override;
	void Render(sf::RenderWindow* window) override;
	void Destroy() override;
};

