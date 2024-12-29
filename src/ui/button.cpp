#include "button.h"

#include "game/game.h"

#define RAYGUI_IMPLEMENTATION
#include "raygui.h"

namespace Brutal
{
void Button::Draw(Vector2 const& position, ButtonComponent& button, u_int64_t uuid)
{
    if (GuiButton((Rectangle){position.x, position.y, button.m_Width, button.m_Height}, button.m_TextField.c_str()) &&
        uuid != 0)
    {
        Game::GetLevel()->m_ScriptCore->AddEvent({EVENT_ONCLICK, uuid});
#ifdef DEBUG
        spdlog::info("Button : text field {}", button.m_TextField);
#endif
    }
};

ButtonComponent Button::Deserialize(json const& json_data)
{
    ButtonComponent button;

    button.m_TextField = json_data["textField"];
    button.m_Width = json_data["width"];
    button.m_Height = json_data["height"];

    return button;
};
}  // namespace Brutal