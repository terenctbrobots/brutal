#include "game.h"

namespace Brutal {
void Game::CreateLevel() { level = std::make_unique<Level>(); }

Game &Game::Get() {
    static Game instance;

    return instance;
}

void Game::Setup(float width, float height) {
    level = nullptr;
    view_screen.x = 0;
    view_screen.y = 0;
    view_screen.width = width;
    view_screen.height = height;

    InitWindow(width, height, "Game");
#ifdef DEBUG
    spdlog::info("Game : Setup with width {} and height {}", width, height);
#endif
}

int Game::MainLoop() {
    if (level == nullptr) return 0;

    level->MainLoop();

    return 0;
}

void Game::Cleanup() {
    level = nullptr;
    CloseWindow();
#ifdef DEBUG
    spdlog::info("Game : Cleanup");
#endif
}

}  // namespace Brutal
