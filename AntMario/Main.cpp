#include "Engine.h"
#include "InputModule.h"

int main()
{

	Engine* engine = Engine::GetInstance();
	engine->Init();



	engine->Run();

}