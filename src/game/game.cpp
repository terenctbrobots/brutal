#include "game.h"

namespace Brutal {
void Game::CreateLevel() {
    level = new Level();
    level->UpdateView({0, 0, width_, height_});
}

Game &Game::Get() {
    static Game instance;

    return instance;
}

void Game::Setup(float width, float height) {
    level = nullptr;

    script_core = new ScriptCore();
    script_core->Setup();
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

    if (script_core != NULL) {
        script_core->Cleanup();
        delete script_core;
    }

    if (level != NULL) {
        delete level;
    }
    CloseWindow();
}

}  // namespace Brutal
