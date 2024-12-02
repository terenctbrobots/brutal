#pragma once

#include "common.h"
#include "raylib.h"

namespace Brutal
{
struct TextComponent
{
    std::string m_TextField;  // TODO: Switch to better string class?
    int m_FontSize = 20;
};

class Text
{
   public:
    static TextComponent Deserialize(json const& json_data);
    static void Draw(Vector2 const& position, TextComponent& text);
};
}  // namespace Brutal