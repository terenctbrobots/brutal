#include "text.h"

namespace Brutal {
void Text::Draw(Vector2 const& position, TextComponent& text) {
    DrawText(text.text_field.c_str(), position.x, position.y, text.font_size, WHITE);
};

TextComponent Text::Deserialize(json const& json_data) {
    TextComponent text;

    text.text_field = json_data["textField"];
    text.font_size = json_data["fontSize"];

    return text;
};
}  // namespace Brutal
