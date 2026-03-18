#include "TimeModule.h"
#include <iostream>

void TimeModule::Init()
{

	deltaClock.restart();

}

void TimeModule::Update()
{

	dt = deltaClock.restart().asSeconds();
	if (dt > 1.f / 60.f)
		dt = 1.f / 60.f;

}

float TimeModule::GetDeltaTime()
{

	return dt;

}