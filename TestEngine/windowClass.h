#pragma once

#include "Win.h"

// class handler for win32
class GameWindow
{
private:
	static LRESULT CALLBACK WindowProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam) noexcept;
	LRESULT messageHandler(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);

private:
	HINSTANCE hInst;
	const wchar_t* windowClassName;
	HWND hWnd;

	int width;
	int height;
	static GameWindow* gameWnd;

public:
	GameWindow(int x, int y, const wchar_t* name, HINSTANCE& hInstance) noexcept;
	~GameWindow() noexcept;
	GameWindow(const GameWindow&) = delete;
	GameWindow& operator=(const GameWindow&) = delete;

	HWND& getHwnd();

};

