#pragma once

#include "raylib.h"

namespace Editor
{
class Window
{
  public:
    bool m_Enabled = true;
    Rectangle m_Bounds;

  public:
    Window() = default;
    ~Window() = default;

    virtual void Draw();
    virtual void Interact(Vector2 click) = 0;
};
} // namespace Editor