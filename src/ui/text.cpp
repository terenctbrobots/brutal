#include "text.h"

namespace Brutal 
{
void Text::Draw(Vector2 const& position, TextComponent& text) 
{
    DrawText(text.m_TextField.c_str(), position.x, position.y, text.m_FontSize, WHITE);
};

TextComponent Text::Deserialize(json const& json_data) 
{
    TextComponent text;

    text.m_TextField = json_data["textField"];
    text.m_FontSize = json_data["fontSize"];

    return text;
};
}  // namespace Brutal
