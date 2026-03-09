#include "TimeModule.h"

void TimeModule::Init()
{

	deltaClock.restart();

}

void TimeModule::Update()
{

	dt = deltaClock.restart().asSeconds();

}