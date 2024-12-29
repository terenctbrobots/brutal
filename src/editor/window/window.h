#pragma once

#include "raylib.h"

namespace Editor
{
class Window
{
   public:
    Rectangle m_Bounds;
    bool m_Enabled = true;

    virtual void Draw();
    virtual void Interact(Vector2 click) = 0;
};
}  // namespace Editor