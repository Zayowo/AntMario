#include "Utils.h"
#include "GameObject.h"

bool IsLoaded(GameObject* gameObject)
{

	if (!ref_renderWindow)
		ref_renderWindow = Engine::GetModule<WindowModule>()->GetRenderWindow();

	return abs(gameObject->GetTransform().pos.x - ref_renderWindow->getView().getCenter().x) < 1000.f;

}