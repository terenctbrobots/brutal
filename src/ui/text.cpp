#include "text.h"

using namespace UI;

Text::Text() {}

Text::~Text() {}

int Text::Load(std::string const& file_name) { return 0; }
void Text::Draw(Vector2 const& position, int16_t tile_id) {
    DrawText(text_field.c_str(), position.x, position.y, font_size, WHITE);
};

int Text::DeSerialize(json const& json_data) { return 0; };