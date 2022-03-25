#pragma once

#define NOMINMAX

#include <Windows.h>
#include <string>
#include <memory>
#include "resource.h"
#include "KeyBoard.h"
#include "RenderV2.h"

// class handler for win32
class window
{
public:
	window(HWND& hWnd, HINSTANCE instanceHandle, int show, RenderV2::FULTEN_DISPLAY_DESC displayDesc);
	window(const window&) = delete;
	window& operator=(const window&) = delete;
	~window();

	KeyBoard kBoard;
	RenderV2& gfx();

	void setWindowName(std::wstring name);

private:
	HWND ghMainWnd;
	std::unique_ptr<RenderV2> graphics;

	// initilizes the windows application
	bool InitWindowsApp(HWND& hWnd, HINSTANCE instanceHandle, int show, RenderV2::FULTEN_DISPLAY_DESC displayDesc);

	static LRESULT CALLBACK WndProcSetup(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);
	static LRESULT CALLBACK WndProcPassthrough(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);
	LRESULT CALLBACK WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);

};