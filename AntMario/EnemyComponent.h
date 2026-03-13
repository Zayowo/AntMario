#pragma once
#include <Component.h>
class EnemyComponent : public Component
{
protected:
	virtual void Init() override;
	virtual void Update(float dt) override {};
	virtual void Render(sf::RenderWindow* window) override {};
	virtual void Destroy() override {};

	void TouchByBall(GameObject* other);
public:
	void Move();
};

