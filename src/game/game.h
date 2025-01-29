#pragma once

#include <memory>

#include "common.h"
#include "game/level.h"
#include "raygui.h"

namespace Brutal
{

class Game
{
  private:
    Game() {}
    float width_;
    float height_;

    Level *m_Level;

  public:
    Game(const Game &) = delete;
    void operator=(const Game &) = delete;

    static Game &Get();
    static Level *GetLevel() { return Get().m_Level; }

    void Setup(float width, float height);
    int MainLoop();
    void Cleanup();

    void CreateLevel();
};
} // namespace Brutal
