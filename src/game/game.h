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

    Level* m_Level;
    Editor::Editor* m_Editor;

   public:
    Game(const Game&) = delete;
    void operator=(const Game&) = delete;

    static Game& Get();
    static Level* GetLevel()
    {
        return Get().m_Level;
    }


    void Setup(float width, float height);
    int MainLoop();
    void Cleanup();

    void CreateLevel();
};
}  // namespace Brutal
