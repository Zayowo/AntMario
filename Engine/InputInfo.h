#pragma once

struct InputInfo
{
	bool isPressedPreviousFrame = false;
	bool isPressed = false;
};

enum class InputState : char
{
	NONE = 'N',
	PRESSED = 'P',
	HELD = 'H',
	RELEASED = 'R'
};