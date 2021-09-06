#include "windowClass.h"

// wrapper for winproc callback
LRESULT CALLBACK GameWindow::WindowProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam) noexcept
{
	if(gameWnd == nullptr)
		return DefWindowProc(hWnd, message, wParam, lParam);
	return gameWnd->messageHandler(hWnd, message, wParam, lParam);
}

LRESULT GameWindow::messageHandler(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	// sort through and find what code to run for each message given
	switch (message)
	{
		// this message is read when the window is closed
	case WM_DESTROY:
		//close application completely
		PostQuitMessage(0);
		return 0;

	default:

		break;
	}
	return DefWindowProc(hWnd, message, wParam, lParam);
}

GameWindow::GameWindow(int x, int y, const wchar_t* name, HINSTANCE& hInstance) noexcept :
	hInst(hInstance),
	windowClassName(name)
{
	// adjust width and height to match the display area
	RECT ws = { 0 };
	ws.left = 100;
	ws.top = 100;
	ws.right = x + ws.left;
	ws.bottom = y + ws.top;
	AdjustWindowRect(
		&ws,
		WS_CAPTION | WS_SIZEBOX | WS_MINIMIZEBOX | WS_MAXIMIZEBOX | WS_SYSMENU,
		false);

	width = ws.right - ws.left;
	height = ws.bottom - ws.top;

	//register windowclass
	WNDCLASSEX wc = { 0 };
	ZeroMemory(&wc, sizeof(wc));
	wc.cbSize = sizeof(wc);
	wc.style = CS_OWNDC;
	wc.lpfnWndProc = WindowProc;
	wc.cbClsExtra = 0;
	wc.cbWndExtra = 0;
	wc.hInstance = hInst;
	wc.lpszClassName = windowClassName;
	wc.hCursor = nullptr;
	wc.hbrBackground = nullptr;
	wc.hIcon = nullptr;
	wc.lpszMenuName = nullptr;
	RegisterClassEx(&wc);

	hWnd = CreateWindowExW(
		0,
		windowClassName,
		name,
		WS_CAPTION | WS_SIZEBOX | WS_MINIMIZEBOX | WS_MAXIMIZEBOX | WS_SYSMENU,
		CW_USEDEFAULT,
		CW_USEDEFAULT,
		width,
		height,
		nullptr,
		nullptr,
		hInst,
		nullptr);

	ShowWindow(hWnd, SW_SHOW);

	gameWnd = this;
}

GameWindow::~GameWindow() noexcept
{
	DestroyWindow(hWnd);
	UnregisterClassW(windowClassName, hInst);
}

HWND& GameWindow::getHwnd()
{
	return hWnd;
}

GameWindow* GameWindow::gameWnd = nullptr;