#include "FireState.h"
#include <Scene.h>
#include <InputModule.h>
#include <Engine.h>
#include <GameObject.h>
#include <SpriteRenderer.h>
#include <VelocityComponent.h>
#include "SquareCollider.h"
#include "FireComponent.h"


void FireState::Enter(PlayerContext& p)
{
	//changement de sprite ?
	p.player->GetTransform().scale = sf::Vector2f(1.f, 1.f);
}


void FireState::Execute(PlayerContext& p, float dt) {
	// create fireball
	Scene* current = p.player->GetScene();
	float direction = 0;
	if (p.player->GetTransform().scale.x <= 0)
		direction = -1;
	else
		direction = 1;

	sf::Vector2f playerPos = p.player->GetTransform().pos;

	InputModule* inputM = Engine::GetModule<InputModule>();

	if (inputM->Is(sf::Keyboard::Key::LShift, InputState::PRESSED)) {
		GameObject* ball = current->CreateGameObject("fireball", { playerPos.x + 20 * direction, playerPos.y - 30 });
		std::cout << "balls" << std::endl;
		ball->AddComponent<SpriteRenderer>("Assets/fireball.png");
		ball->AddComponent<SquareCollider>(sf::Vector2f(14.f, 14.f));
		ball->AddComponent<FireComponent>();
		VelocityComponent* veloBall = ball->AddComponent<VelocityComponent>(360.f);
		veloBall->SetVelocity(sf::Vector2f(direction, 0.f));
	}


	//current->CreateGameObject("fireBall", sf::Vector2f(playerPos.x * direction, playerPos.y));

}