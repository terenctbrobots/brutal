#ifndef GAME_H
#define GAME_H

#include <memory>

#include "common.h"
#include "level.h"
#include "raygui.h"
#include "script/scriptcore.h"

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
    ScriptCore* script_core;

    void Setup(float width, float height);
    int MainLoop();
    void Cleanup();

    void CreateLevel();
};
}  // namespace Brutal

#endif