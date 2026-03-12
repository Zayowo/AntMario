#include "TimeModule.h"
#include <iostream>

void TimeModule::Init()
{

	deltaClock.restart();

}

void TimeModule::Update()
{

	dt = (deltaClock.restart().asSeconds() * speed);

}

float TimeModule::GetDeltaTime()
{

	return dt;

}

float& TimeModule::GetSpeed()
{

	return speed;

}