#include "FireState.h"
#include <Scene.h>
#include <InputModule.h>
#include <Engine.h>
#include <GameObject.h>
#include <SpriteRenderer.h>
#include <VelocityComponent.h>
#include "SquareCollider.h"
#include "FireComponent.h"


void FireState::Enter(PlayerContext& ctx)
{
	//changement de sprite ?
	ctx.player->GetTransform().scale = sf::Vector2f(1.f, 1.f);
	ctx.isInFireFlower = true;

}


void FireState::Execute(PlayerContext& ctx, float dt) {
	// create fireball
	Scene* current = ctx.player->GetScene();
	float direction = 0;
	if (ctx.player->GetTransform().scale.x <= 0)
		direction = -1;
	else
		direction = 1;

	sf::Vector2f playerPos = ctx.player->GetTransform().pos;

	InputModule* inputM = Engine::GetModule<InputModule>();

	std::vector<GameObject*> fireballs = current->GetGameObjectsByName("Fireball");
	if (inputM->Is(sf::Keyboard::Key::LShift, InputState::PRESSED)) {
		if (fireballs.size() < 2) {
			GameObject* ball = current->CreateGameObject("Fireball", { playerPos.x + 20 * direction, playerPos.y - 30 });
			std::cout << "balls" << std::endl;
			ball->AddComponent<SpriteRenderer>("Assets/fireball.png");
			float scale = 1.25f;
			ball->GetTransform().scale = sf::Vector2f(scale, scale);
			ball->AddComponent<SquareCollider>(sf::Vector2f(14.f * scale, 14.f * scale));
			ball->AddComponent<FireComponent>();
			VelocityComponent* veloBall = ball->AddComponent<VelocityComponent>(500.f);
			veloBall->SetVelocity(sf::Vector2f(direction, 0.f));
		}
	}


	//current->CreateGameObject("fireBall", sf::Vector2f(playerPos.x * direction, playerPos.y));

}