#include "Engine.h"

int main()
{

	Engine* engine = Engine::GetInstance();
	engine->Init();

	engine->Run();

}