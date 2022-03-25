// Date: 8/21/2021
// purpose: create a basic directx based framework
// for small projects

#include <chrono>
#include <string>
#include "Game.h"

// main handle for window
HWND ghMainWnd = 0;

// main
int CALLBACK WinMain(
	_In_ HINSTANCE hInstance,
	_In_opt_ HINSTANCE hPrevInstance,
	_In_ LPSTR lpCmdLine,
	_In_ int nCmdShow)
{
	try
	{
		// setup a std::chrono clock to normalize for time
		std::chrono::steady_clock timer;
		std::chrono::steady_clock::time_point lastTimeFrame = timer.now();
		std::chrono::duration<float> deltaTime;

		// fill out struct to format size and color output of display
		RenderV2::FULTEN_DISPLAY_DESC dd;
		ZeroMemory(&dd, sizeof(dd));
		dd.nScreenWidth = 800;
		dd.nScreenHeight = 600;
		dd.fColorFormat = DXGI_FORMAT_R8G8B8A8_UNORM;
		
		// create game object
		Game game(ghMainWnd, hInstance, nCmdShow, dd);
		
		
		MSG msg = { 0 };

		while (msg.message != WM_QUIT)
		{
			if(PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
			{
				TranslateMessage(&msg); // translate keystroke messages into a usable format 
				DispatchMessageW(&msg); // send the message to the WindowProc function 
			}

			// calculate the time since game loop
			deltaTime = std::chrono::duration_cast<std::chrono::duration<float>>(timer.now() - lastTimeFrame);
			lastTimeFrame = timer.now();


			// run game 
			game.doTick(deltaTime.count());

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
