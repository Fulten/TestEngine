#pragma once

// the game's main class
#include "window.h"

class Game 
{
private:
    std::unique_ptr<window> gameWindow;

public:
    Game(HWND& hWnd, HINSTANCE instanceHandle, int show, RenderV2::FULTEN_DISPLAY_DESC displayDescription);
    Game(const Game&) = delete;
    Game& operator=(const Game&) = delete;
    ~Game();
    void doTick(float deltaTime);
    void updateState(float deltaTime);
    void updateGraphics();

};

