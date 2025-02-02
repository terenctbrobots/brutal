#pragma once

#include <string>
#include "raylib.h"
#include "raygui.h"

namespace Editor 
{
class Component
{
    public:
        bool m_Enabled = true;
        Rectangle m_Bounds;

        char m_Name[255] = "Game Object";
    public:
        Component() = default;
        ~Component() = default;

        virtual void Resize();
        virtual void Draw();
        virtual void Interact(Vector2 click) = 0;
};
}