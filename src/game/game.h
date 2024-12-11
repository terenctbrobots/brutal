#pragma once 

#include <memory>

#include "common.h"
#include "level.h"
#include "raygui.h"
#include "editor/editor.h"

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
    static Level* GetLevel()
    {
        return Get().level;
    }

    Level* level;
    Editor* m_editor;

    void Setup(float width, float height);
    int MainLoop();
    void Cleanup();

    void CreateLevel();
};
}  // namespace Brutal
