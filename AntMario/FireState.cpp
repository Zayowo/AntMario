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

	ctx.player->GetComponent<SquareCollider>()->SetSize(sf::Vector2f(30.f, 115.f));
	ctx.isWalking = false;
	ctx.isInFireFlower = true;

}


void FireState::Execute(PlayerContext& ctx, float dt) {

	SpriteRenderer* spriteRenderer = ctx.player->GetComponent<SpriteRenderer>();

	if (ctx.invulnerability > 0) {
		ctx.invulnerability -= dt;
		// Flash effect during invulnerability
		int flashCount = (int)(ctx.invulnerability * 4); // Flash 4 times per second
		if (flashCount % 2 == 0) {
			sf::Color color = spriteRenderer->GetColor();
			color.a = 100; // Semi-transparent
			spriteRenderer->SetColor(color);
		} else {
			sf::Color color = spriteRenderer->GetColor();
			color.a = 255; // Full opacity
			spriteRenderer->SetColor(color);
		}
	} else {
		// Make sure sprite is fully visible after invulnerability ends
		sf::Color color = spriteRenderer->GetColor();
		color.a = 255;
		spriteRenderer->SetColor(color);
	}

	const float velocityX = ctx.player->GetComponent<VelocityComponent>()->GetVelocity().x;
	if (velocityX != 0.f && !ctx.isWalking)
	{
		ctx.isWalking = true;
		ctx.player->GetComponent<SpriteRenderer>()->SetAnimationRule(SpriteAnimationRule(sf::Vector2i(0, 256), sf::Vector2i(128, 128), 4));
	}
	else if (velocityX == 0.f && ctx.isWalking)
	{
		ctx.isWalking = false;
		ctx.player->GetComponent<SpriteRenderer>()->SetAnimationRule(SpriteAnimationRule(sf::Vector2i(0, 256), sf::Vector2i(128, 128), 1));
	}

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

void FireState::Exit(PlayerContext& ctx)
{

	ctx.isInFireFlower = false;

}