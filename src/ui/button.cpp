#include "button.h"

#define RAYGUI_IMPLEMENTATION
#include "raygui.h"

namespace Brutal {
void Button::Draw(Vector2 const& position, ButtonComponent& button) {
    GuiButton((Rectangle){position.x, position.y, button.width, button.height}, button.text_field.c_str());

    // TODO: Trigger script call here
};

ButtonComponent Button::Deserialize(json const& json_data) {
    ButtonComponent button;

    button.text_field = json_data["textField"];
    button.width = json_data["width"];
    button.height = json_data["height"];

    return button;
};
}  // namespace Brutal