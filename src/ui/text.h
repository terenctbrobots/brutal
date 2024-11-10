#ifndef TEXT_H_
#define TEXT_H_
#include "common.h"
#include "raylib.h"

namespace Brutal {
struct TextComponent {
    std::string text_field;  // TODO: Switch to better string class?
    int font_size = 20;
};

class Text {
   public:
    static TextComponent Deserialize(json const& json_data);
    static void Draw(Vector2 const& position, TextComponent& text);
};
}  // namespace Brutal

#endif