#include "game.h"

Game::Game(float width, float height)
{
    level = nullptr;
    view_screen.x = 0;
    view_screen.y = 0;
    view_screen.width = width;
    view_screen.height = height;

    InitWindow(width, height, "Game");
}

Game::~Game()
{
    CloseWindow();
}

std::shared_ptr<Level> Game::CreateLevel(std::shared_ptr<Level> new_level)
{
    new_level->view_screen = &view_screen;

    return new_level;
}

int Game::MainLoop()
{
    if (level == nullptr)
        return 0;

    level->MainLoop();

    return 0;
}