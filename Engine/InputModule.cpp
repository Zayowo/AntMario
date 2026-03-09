#include <iostream>
#include "InputModule.h"

void InputModule::Update()
{

	for (auto& [key, info] : keyInfoMap)
	{
		info.isPressedPreviousFrame = info.isPressed;
		info.isPressed = sf::Keyboard::isKeyPressed(key);
	}

	for (auto& [button, info] : buttonInfoMap)
	{
		info.isPressedPreviousFrame = info.isPressed;
		info.isPressed = sf::Mouse::isButtonPressed(button);
	}

}

void InputModule::RegisterInput(sf::Keyboard::Key key)
{

	if (keyInfoMap.contains(key))
		return;

	keyInfoMap[key] = InputInfo();

}

void InputModule::RegisterInput(sf::Mouse::Button button)
{

	if (buttonInfoMap.contains(button))
		return;

	buttonInfoMap[button] = InputInfo();

}

bool InputModule::Is(sf::Keyboard::Key key, InputState state)
{

	if (!keyInfoMap.contains(key))
		return false;

	return state == GetState(keyInfoMap[key]);

}

bool InputModule::Is(sf::Mouse::Button button, InputState state)
{

	if (!buttonInfoMap.contains(button))
		return false;

	return state == GetState(buttonInfoMap[button]);

}

InputState InputModule::GetState(InputInfo info)
{

	if (info.isPressedPreviousFrame && info.isPressed)
		return InputState::HELD;

	else if (info.isPressedPreviousFrame && !info.isPressed)
		return InputState::RELEASED;

	else if (!info.isPressedPreviousFrame && info.isPressed)
		return InputState::PRESSED;

	return InputState::NONE;

}