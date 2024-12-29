#include "game.h"

namespace Brutal
{
void Game::CreateLevel()
{
    m_Level = new Level();
    m_Level->Setup(width_, height_);
    m_Level->UpdateView({0, 0, width_, height_});
}

Game &Game::Get()
{
    static Game instance;

    return instance;
}

void Game::Setup(float width, float height)
{
    m_Level = NULL;

    width_ = width;
    height_ = height;

    InitWindow(width, height, "Game");

#ifdef DEBUG
    spdlog::info("Game : Setup with width {} and height {}", width, height);
#endif
}

int Game::MainLoop()
{
    if (m_Level == NULL)
        return 0;

    m_Level->MainLoop();

    return 0;
}

void Game::Cleanup()
{
#ifdef DEBUG
    spdlog::info("Game : Cleanup");
#endif

    if (m_Level != NULL)
    {
        m_Level->Cleanup();
        delete m_Level;
    }

    CloseWindow();
}

} // namespace Brutal
