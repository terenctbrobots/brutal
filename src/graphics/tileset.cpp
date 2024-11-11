#include "tileset.h"

#include <fstream>
#include <iostream>

#include "helper.h"

using namespace Brutal;

TileSet::TileSet() { texture_.id = 0; }

TileSet::~TileSet() {
    if (texture_.id > 0) {
        UnloadTexture(texture_);
    }
}

int TileSet::Deserialize(json const& json_data) {
    std::string file_name = json_data["image"];
    texture_ = LoadTexture(file_name.c_str());

    if (texture_.id == 0) {
        spdlog::error("TileSet: could not load texture named {}", file_name);
        abort();
    }
#ifdef DEBUG
    spdlog::info("TileSet: Loaded texture {}", file_name);
#endif

    width = json_data["imagewidth"];
    height = json_data["imageheight"];

    tile_width = json_data["tilewidth"];
    tile_height = json_data["tileheight"];

    name = json_data["name"];

    tile_count = json_data["tilecount"];

    float tile_x = 0;
    float tile_y = 0;

    for (int i = 0; i < tile_count; i++) {
        tile_list_.push_back({tile_x, tile_y, tile_width, tile_height});
        tile_x += tile_width;

        if (tile_x >= width) {
            tile_x = 0;
            tile_y += tile_height;
        }
    }

    return 0;
}

void TileSet::Draw(Vector2 const& position, uint16_t tile_id) {
    DrawTextureRec(texture_, tile_list_[tile_id], position, WHITE);
}

void TileSet::DrawRectangle(Vector2 const& position, Rectangle const& rectangle) {
    DrawTextureRec(texture_, rectangle, position, WHITE);
}