#include "FireState.h"
#include <Scene.h>
#include <InputModule.h>
#include <Engine.h>
#include <GameObject.h>
#include <SpriteRenderer.h>

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
		GameObject* ball = current->CreateGameObject("fireball", sf::Vector2f(200, 200));
		std::cout << "balls" << std::endl;
		ball->AddComponent<SpriteRenderer>("Assets/fireball.png");
		
	}


	//current->CreateGameObject("fireBall", sf::Vector2f(playerPos.x * direction, playerPos.y));

}