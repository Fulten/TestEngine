// Date: 8/21/2021
// purpose: create a basic directx based framework
// for small projects

#include <chrono>
#include <Windows.h>
#include <windowsx.h>
#include "Game.h"

// hight and width of window
int windowWidth = 900;
int windowHight = 800;

std::wstring windowName = L"EngineTest | fps:";

LRESULT CALLBACK WindowProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
void copy(wchar_t* recive, const wchar_t* target, int maxSize);
void append(wchar_t* first, const char* second, int maxSize);

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	// handle for the window
	HWND hWnd;
	// this struct holds information for the window class
	WNDCLASSEX wc;

	// Clear out the window class of use
	ZeroMemory(&wc, sizeof(WNDCLASSEX));

	// fill in the wndclassex struct with the needed information
	wc.cbSize = sizeof(WNDCLASSEX);
	wc.style = CS_HREDRAW | CS_VREDRAW;
	wc.lpfnWndProc = WindowProc;
	wc.hInstance = hInstance;
	wc.hIcon = LoadIcon(wc.hInstance, MAKEINTRESOURCE(101));
	wc.hCursor = LoadCursor(NULL, IDC_ARROW);
	wc.hbrBackground = (HBRUSH)COLOR_WINDOW;
	wc.lpszClassName = L"WindowClass1";
	wc.hIconSm = LoadIcon(wc.hInstance, MAKEINTRESOURCE(IDI_APPLICATION));

	// register windows class
	RegisterClassEx(&wc);

	// create the window and use the result as the handle
	hWnd = CreateWindowEx(NULL,
		L"WindowClass1", // name of the window class
		windowName.c_str(), // title of the window
		WS_OVERLAPPEDWINDOW, // window style
		300, // x position of the window
		100, // y position of the window
		windowWidth, // width of the window
		windowHight, // hight of the window 
		NULL, // we have no parent window
		NULL, // we are not useing menus
		hInstance, // application handle
		NULL); // used with multiple windows

	// display the window on the screen
	ShowWindow(hWnd, nCmdShow);
	MSG msg;

	// settup a std::chrono clock to normalize for time
	std::chrono::steady_clock timer;
	std::chrono::steady_clock::time_point lastTimeFrame = timer.now();
	std::chrono::duration<float> deltaTime;

	float fps = 0;

	try
	{
		Game game(hWnd);

		while (true)
		{
			while (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
			{
				TranslateMessage(&msg); // translate keystroke messages into a usable format
				DispatchMessageW(&msg); // send the message to the WindowProc function

				if (msg.message == WM_QUIT)
					goto exit;
			}

			// calculate the time since last frame
			deltaTime = std::chrono::duration_cast<std::chrono::duration<float>>(timer.now() - lastTimeFrame);
			lastTimeFrame = timer.now();

			// fps counter
			fps = 1 / deltaTime.count();
			SetWindowTextW(hWnd, (windowName + std::to_wstring(fps)).c_str());

			// run game 
			game.doTick(deltaTime.count());

			Sleep(1);
		}
	}
	catch (FultenException error) 
	{
		// translate error code into something useful
		std::wstring temp = L"Error Caught in main: ";
		temp +=error.getMessageW();
		temp += L", At line : ";
		temp += error.getLine();
		OutputDebugStringW(temp.c_str());
		return -1;
	}

exit:
	return msg.wParam;
}

LRESULT CALLBACK WindowProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	// sort through and find what code to run for each message given
	switch (message)
	{
		// this message is read when the window is closed
	case WM_DESTROY:
	{
		//close application completely
		PostQuitMessage(0);
		return 0;
	} break;

	default:
	{

	} break;
	}

	return DefWindowProc(hWnd, message, wParam, lParam);
}