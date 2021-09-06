// Date: 8/21/2021
// purpose: create a basic directx based framework
// for small projects

#include "windowClass.h"
#include <chrono>
#include "Game.h"

// hight and width of window
int windowWidth = 800, windowHeight = 600;
std::wstring windowName = L"EngineTest | fps:";

// main
int CALLBACK WinMain(
	HINSTANCE hInstance,
	HINSTANCE hPrevInstance,
	LPSTR lpCmdLine,
	int nCmdShow)
{
	// make the window actually show
	
	MSG msg;

	// setup a std::chrono clock to normalize for time
	std::chrono::steady_clock timer;
	std::chrono::steady_clock::time_point lastTimeFrame = timer.now();
	std::chrono::duration<float> deltaTime;

	float fps = 0;
	bool exit = false;

	try
	{
		GameWindow wnd(windowWidth, windowHeight, windowName.c_str(), hInstance);

		Game game(wnd.getHwnd());

		while (!exit)
		{
			while (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
			{
				TranslateMessage(&msg); // translate keystroke messages into a usable format
				DispatchMessageW(&msg); // send the message to the WindowProc function

				if (msg.message == WM_QUIT)
					exit = true;
			}

			// calculate the time since last frame
			deltaTime = std::chrono::duration_cast<std::chrono::duration<float>>(timer.now() - lastTimeFrame);
			lastTimeFrame = timer.now();

			// fps counter
			fps = 1 / deltaTime.count();
			SetWindowTextW(wnd.getHwnd(), (windowName + std::to_wstring(fps)).c_str());

			// run game 
			game.doTick(deltaTime.count());

			Sleep(1);
		}
	}
	catch (FultenException error) 
	{
		// translate exception into something more useful
		std::wstring temp = L"Error Caught in main: ";
		temp +=error.getMessageW();
		temp += L"\n, In file: ";
		temp += error.getFileW();
		temp += L"\n, At line: ";
		temp += std::to_wstring(error.getLine());
		temp += L"\n, Desc: ";
		temp += error.getDescW();
		temp += '\n';
		OutputDebugStringW(temp.c_str());
		return -1;
	}

	return 0;
}
