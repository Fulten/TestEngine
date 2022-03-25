#pragma once

#define NOMINMAX

#include <windows.h>
#include <bitset>
#include <queue>


class KeyBoard
{
	friend class window;
private:
	std::bitset<256> keyStates;

public:
	KeyBoard();
	~KeyBoard();

	// returns the current keystate of a given keycode
	bool getKeyState(unsigned char keyCode);

private:
	void onDown(unsigned char keyCode); // used by window to signal an ondown event
	void onUp(unsigned char keyCode); // used by window to signal an onup event
	void onChar(unsigned char keyCode); // used by window to signal an onchar event
	void clearKeyStates(); // resets the current keystates

};

