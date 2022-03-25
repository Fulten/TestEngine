#include "Game.h"

// constructor
Game::Game(HWND& hWnd, HINSTANCE instanceHandle, int show, RenderV2::FULTEN_DISPLAY_DESC displayDescription)
{
	gameWindow = std::make_unique<window>(hWnd, instanceHandle, show, displayDescription);
}

// destructor
Game::~Game()
{}

// preformed every frame
void Game::doTick(float deltaTime)
{
	// update the game logic
	updateState(deltaTime);
	// update the graphical component
	updateGraphics();

	// clears the background state
	gameWindow->gfx().ClearBackground(0.0f, 0.0f, 0.0f);
	// test function
	gameWindow->gfx().DrawTestTriangle();
	// flip the back buffers and present the next frame to the screen
	gameWindow->gfx().PresentFrame();
}

// update the state of the game
void Game::updateState(float deltaTime)
{
	// name of the window
	std::wstring windowName = L"EngineTest | fps: ";
	// fps counter 
	float fps = 1 / deltaTime;

	gameWindow->setWindowName(windowName + std::to_wstring(fps));

}

// update the graphical component of the game
void Game::updateGraphics()
{
	

}
