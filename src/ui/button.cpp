#include "button.h"
#include "game/game.h"

#define RAYGUI_IMPLEMENTATION
#include "raygui.h"

namespace Brutal {
void Button::Draw(Vector2 const& position, ButtonComponent& button, u_int64_t uuid) {
    if (GuiButton((Rectangle){position.x, position.y, button.width, button.height}, button.text_field.c_str()) &&
    uuid != 0) {
        Game& game = Game::Get();
        game.level->script_core->AddEvent({EVENT_ONCLICK, uuid});
    }
};

ButtonComponent Button::Deserialize(json const& json_data) {
    ButtonComponent button;

    button.text_field = json_data["textField"];
    button.width = json_data["width"];
    button.height = json_data["height"];

    return button;
};
}  // namespace Brutal