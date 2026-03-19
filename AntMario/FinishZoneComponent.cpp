#include "FinishZoneComponent.h"
#include <GameObject.h>
#include <SquareCollider.h>
#include <Scene.h>
#include <SceneModule.h>
#include <Engine.h>

void FinishZoneComponent::Init()
{
	SquareCollider* collider = owner->GetComponent<SquareCollider>();

	if (!collider)
	{
		std::cerr << "FinishZoneComponent: No SquareCollider detected!" << std::endl;
		return;
	}

	collider->RegisterCallback("Player", [this](GameObject* player) {
		
		if (!hasTriggered)
		{
			hasTriggered = true;
			Engine::GetModule<SceneModule>()->SetScene("VictoryScene");
		}

	});
}

void FinishZoneComponent::Update(float dt)
{
}
