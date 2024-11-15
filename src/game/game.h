#pragma once 

#include <memory>

#include "common.h"
#include "level.h"
#include "raygui.h"

namespace Brutal {

class Game {
   private:
    Game() {}
    float width_;
    float height_;

   public:
    Game(const Game&) = delete;
    void operator=(const Game&) = delete;

    static Game& Get();
    Level* level;

    void Setup(float width, float height);
    int MainLoop();
    void Cleanup();

    void CreateLevel();
};
}  // namespace Brutal
