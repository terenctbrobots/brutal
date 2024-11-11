#include "tileset.h"

#include <fstream>

#include "helper.h"

using namespace Brutal;

TileSet::TileSet() {
    tile_first_id = 1;
    texture_.id = 0;
}

TileSet::~TileSet() {
    if (texture_.id > 0) {
        UnloadTexture(texture_);
    }
}

int TileSet::Deserialize(json const& json_data) {
    // TODO: Standarize to fileName later
    std::string file_name = json_data["image"];
    texture_ = LoadTexture(file_name.c_str());

    if (texture_.id == 0) {
        spdlog::error("TileSet: could not load texture named {}", file_name);
        abort();
    }

    width = json_data["imagewidth"];
    height = json_data["imageheight"];

    tile_width = json_data["tilewidth"];
    tile_height = json_data["tileheight"];

    name = json_data["name"];

    tile_count = json_data["tilecount"];

    float tile_x, tile_y = 0;

    for (int i = 0; i < tile_count; i++) {
        tile_list_.push_back(
            std::unique_ptr<Rectangle>(new Rectangle{tile_x, tile_y, (float)tile_width, (float)tile_height}));
        tile_x += tile_width;

        if (tile_x >= width) {
            tile_x = 0;
            tile_y += tile_height;
        }
    }

    return 0;
}

void TileSet::Draw(Vector2 const& position, int16_t tile_id) {
    int32_t offset_tile_id = tile_id - tile_first_id;

#ifdef DEBUG
    if (offset_tile_id == 0 || offset_tile_id >= tile_count) {
        spdlog::warn("TileSet: tile id {} is invalid", tile_id);
        return;
    }
#endif

    DrawTextureRec(texture_, *tile_list_[offset_tile_id], position, WHITE);
}