#pragma once

// the game's main class

#include "Render.h"
#include "Map.h"

class Game :
    public Render
{
private:



public:
    Game(HWND hWnd);
    ~Game();
    void doTick(float deltaTime);
    void updateState();
    void updateGraphics();

};

