#include "TimeModule.h"
#include <iostream>

void TimeModule::Init()
{

	deltaClock.restart();

}

void TimeModule::Update()
{

	dt = deltaClock.restart().asSeconds();
	std::cout << 1.f / dt << std::endl;

}

float TimeModule::GetDeltaTime()
{

	return dt;

}