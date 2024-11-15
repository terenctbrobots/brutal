#include "game.h"

namespace Brutal {
void Game::CreateLevel() {
    level = std::make_unique<Level>();
    level->Setup();
    level->UpdateView({0, 0, width_, height_});
}

Game &Game::Get() {
    static Game instance;

    return instance;
}

void Game::Setup(float width, float height) {
    level = nullptr;

    width_ = width;
    height_ = height;

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
#ifdef DEBUG
    spdlog::info("Game : Cleanup");
#endif

    if (level) {
        level->Cleanup();
        level = nullptr;
    }

    CloseWindow();
}

}  // namespace Brutal
