#ifndef GAME_H
#define GAME_H
#include <cstdint>
#include <memory>

#include "level.h"
#include "raylib.h"

namespace Brutal {

class Game {
   private:
    Game() {}

   public:
    Game(const Game&) = delete;
    void operator=(const Game&) = delete;

    static Game& Get();
    Rectangle view_screen;
    std::unique_ptr<Level> level;

    void Setup(float width, float height);
    int MainLoop();
    void Cleanup();

    void CreateLevel();
};
}  // namespace Brutal

#endif