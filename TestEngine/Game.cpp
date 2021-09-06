#include "Game.h"

Game::Game(HWND& hWnd) :
	graphics(hWnd)
{}

Game::~Game()
{}

// preformed every frame
void Game::doTick(float deltaTime)
{
	updateState();
	updateGraphics();
	// builds the next frame
	graphics.build();
	// sends the built frame to the graphics card
	graphics.present(); 
}

// update the state of the game
void Game::updateState()
{

}

// update the graphical component of the game
void Game::updateGraphics()
{
	

}
