#pragma once

// the game's main class

#include "Draw.h"
#include "Map.h"

class Game 
{
private:
    Draw graphics;


public:
    Game(HWND& hWnd);
    ~Game();
    void doTick(float deltaTime);
    void updateState();
    void updateGraphics();

};

