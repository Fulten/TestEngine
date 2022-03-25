#include "window.h"


// constructor
window::window(HWND& hWnd,
	HINSTANCE instanceHandle,
	int show,
	RenderV2::FULTEN_DISPLAY_DESC displayDesc) :
	kBoard()
{
	ghMainWnd = hWnd;
	if (!InitWindowsApp(ghMainWnd, instanceHandle, show, displayDesc))
		return;

}

// destructor
window::~window()
{
	DestroyWindow(ghMainWnd);
}

// used to access graphics component
RenderV2& window::gfx()
{
	return *graphics;
}

// sets the name of the window
void window::setWindowName(std::wstring name)
{
	SetWindowTextW(ghMainWnd, name.c_str());
}

// contains the initilization steps for creating our window
bool window::InitWindowsApp(HWND& hWnd,
	HINSTANCE instanceHandle,
	int show,
	RenderV2::FULTEN_DISPLAY_DESC displayDesc)
{
	// The first task to creating a window is to describe some of its 
	// characteristics by filling out a WNDCLASSEX structure.
	WNDCLASSEX wc;
	ZeroMemory(&wc, sizeof(wc));

	HICON hIcon1 = LoadIcon(instanceHandle, MAKEINTRESOURCE(IDI_ICON1));

	wc.cbSize = sizeof(wc);
	wc.style = CS_OWNDC;
	wc.lpfnWndProc = WndProcSetup; // pass our special wndproc setup function
	wc.cbClsExtra = 0;
	wc.cbWndExtra = 0;
	wc.hInstance = instanceHandle; // handle to our instance
	wc.hIcon = hIcon1;
	wc.hCursor = LoadCursor(0, IDC_ARROW);
	wc.hbrBackground = nullptr; //(HBRUSH)GetStockObject(WHITE_BRUSH);
	wc.lpszMenuName = 0;
	wc.lpszClassName = L"BasicWndClass";
	wc.hIconSm = hIcon1;

	// register this WNDCLASS instance with Windows so 
	// that we can create a window based on it.
	if (!RegisterClassEx(&wc)) // makes sure it was successfully registered
	{
		MessageBox(0, L"RegisterClass FAILED", 0, 0);
		return false;
	}

	// define a RECT struct and fill it out with the desired dimensions of our window
	RECT windowBox;
	windowBox.left = 0;
	windowBox.top = 0;
	windowBox.right = displayDesc.nScreenWidth;
	windowBox.bottom = displayDesc.nScreenHeight;

	// using adjustWindowRect we adjust the size of windowBox so that the screen area matches our initilized values
	AdjustWindowRect(&windowBox, WS_OVERLAPPEDWINDOW, false);

	// creates a window with defined parameters using application handle
	ghMainWnd = CreateWindow(
		L"BasicWndClass", // Registered WNDCLASS instance to use.
		L"Directx11 TestWindow", // window title
		WS_CAPTION | WS_MINIMIZEBOX | WS_MAXIMIZEBOX | WS_SYSMENU | WS_SIZEBOX, // style flags
		CW_USEDEFAULT, // x-coordinate
		CW_USEDEFAULT, // y-coordinate
		windowBox.right, // width
		windowBox.bottom, // height
		nullptr, // parent window
		nullptr, // menu handle
		instanceHandle, // app instance
		this); // extra creation parameters

	if (ghMainWnd == 0) // check that our window was actually created
	{
		MessageBox(0, L"CreateWindow FAILED", 0, 0);
		return false;
	}

	// presents our window
	ShowWindow(ghMainWnd, show);
	UpdateWindow(ghMainWnd);

	// create graphics object
	graphics = std::make_unique<RenderV2>(hWnd, displayDesc);

	// returns true if window creation was successful
	return true;
}

// static function used to setup wndproc to use class function to handle messages
LRESULT window::WndProcSetup(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	// on nonclient create message,
	if (msg == WM_NCCREATE)
	{
		// use create struct to retrive creation information about our windows class
		const CREATESTRUCTW* const pCreate = reinterpret_cast<CREATESTRUCTW*>(lParam);
		// create a pointer to our window object
		window* const pWnd = static_cast<window*>(pCreate->lpCreateParams);
		// store the pointer to our window object in the userdata of the windows app
		// chili you ingenius bastard
		SetWindowLongPtr(hWnd, GWLP_USERDATA, reinterpret_cast<LONG_PTR>(pWnd));
		// set the windows callback proc to use a passthrough function instead
		SetWindowLongPtr(hWnd, GWLP_WNDPROC, reinterpret_cast<LONG_PTR>(&window::WndProcPassthrough));

		// pass to standerd windows proc
		return pWnd->WndProc(hWnd, msg, wParam, lParam);
	}
	// use default proc for any other message
	return DefWindowProc(hWnd, msg, wParam, lParam);
}

// used to pass messages to our class based wndproc
LRESULT window::WndProcPassthrough(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	// retrive window data containing pointer to our window's class
	window* const pWnd = reinterpret_cast<window*>(GetWindowLongPtr(hWnd, GWLP_USERDATA));
	return pWnd->WndProc(hWnd, msg, wParam, lParam);
}

// windows procedure
LRESULT window::WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	//fultenDebug::ShowMessageTextEx(msg, wParam);

	switch (msg)
	{
	case WM_KEYDOWN:
		kBoard.onDown(static_cast<unsigned char>(wParam));

		return 0;

	case WM_KEYUP:
		kBoard.onUp(static_cast<unsigned char>(wParam));

		return 0;


	case WM_KILLFOCUS:
		kBoard.clearKeyStates();

		return 0;

		// prompts the user with a confirmation box when attempting to close the window
	case WM_CLOSE:
		if (MessageBox(window::ghMainWnd, L"Exit Window", L"Are you sure?", MB_OKCANCEL | MB_ICONEXCLAMATION) == IDOK)
			DestroyWindow(ghMainWnd);
		return 0;

		// In the case of a destroy message, then send a 
		// quit message, which will terminate the message loop.
	case WM_DESTROY:
		PostQuitMessage(0);
		return 0;
	}

	// Forward any other messages we did not handle above to the 
	// default window procedure. Note that our window procedure
	// must return the return value of DefWindowProc.
	return DefWindowProc(hWnd, msg, wParam, lParam);
}
