#include "KeyBoard.h"

KeyBoard::KeyBoard()
{
}

KeyBoard::~KeyBoard()
{
}

void KeyBoard::onDown(unsigned char keyCode)
{
	keyStates[keyCode] = true;
}

void KeyBoard::onUp(unsigned char keyCode)
{
	keyStates[keyCode] = false;
}

void KeyBoard::onChar(unsigned char keyCode)
{}

void KeyBoard::clearKeyStates()
{
	keyStates.reset();
}

bool KeyBoard::getKeyState(unsigned char keyCode)
{
	return keyStates[keyCode];
}
