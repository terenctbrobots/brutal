#include "button.h"

#include "raylib.h"

#define RAYGUI_IMPLEMENTATION
#include "raygui.h"

using namespace Brutal;

Button::Button() {}

Button::~Button() {}

int Button::Load(std::string const& file_name) { return 0; }
void Button::Draw(Vector2 const& position) {
    GuiButton((Rectangle){position.x, position.y, width, height}, text_field.c_str());

    // TODO: trigger script here but calling a OnClick function
}

int Button::DeSerialize(json const& json_data) { return 0; };