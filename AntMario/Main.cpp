#include "Engine.h"
#include "InputModule.h"

int main()
{

	Engine* engine = Engine::GetInstance();
	engine->Init();

	auto inputModule = Engine::GetModule<InputModule>();

	engine->Run();

}