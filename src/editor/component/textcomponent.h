#pragma once

#include "editor/component/component.h"

namespace Editor
{
class TextComponent : public Component
{
    public:
        TextComponent() = default;
        ~TextComponent() = default;

        void Resize() override final;
        void Draw() override final;
        void Interact(Vector2 click) override final;

};       
}