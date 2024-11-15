#include "tilesetpack.h"

#include <iostream>

namespace Brutal {

TileSetPack::TileSetPack() {}

TileSetPack::~TileSetPack() {}

int TileSetPack::Load(std::string const& filename) {
    // std::shared_ptr<TileSet> new_tileset = std::make_shared<TileSet>();

    // int ret_value = new_tileset->Load(filename);

    // if (ret_value != 0) {
    //     return ret_value;
    // }

    // new_tileset->tile_first_id = current_tile_id_index_;
    // new_tileset->tile_last_id = new_tileset->tile_first_id + new_tileset->tile_count;

    // current_tile_id_index_ += new_tileset->tile_count;

    return 0;
}

void TileSetPack::Deserialize(json const& json_data) {
    // Tile_id 0 is a blank

    tileset_.push_back({nullptr, NULL});

    for (auto& tileset_data : json_data) {
        auto tileset = std::make_shared<TileSet>();
        tileset->Deserialize(tileset_data);

        uint32_t tile_count = tileset->tile_count;

        for (int i = 0; i < tile_count; i++) {
            tileset_.push_back({tileset, &tileset->tile_list_[i]});
        }
        current_tile_id_index_ += tile_count;
#ifdef DEBUG
        spdlog::info("TileSetPack: {} tiles loaded", tile_count);
#endif
    }

    auto& tuple = tileset_[1];
    tile_width_ = std::get<0>(tuple)->tile_width;
    tile_height_ = std::get<0>(tuple)->tile_height;
}

void TileSetPack::Draw(Vector2 const& position, uint16_t tile_id) {
    if (tile_id >= current_tile_id_index_ || tile_id == 0) {
        spdlog::error("TileSetPack: trying to draw a unknown tile {}", tile_id);
        abort();
    }

    auto& tuple = tileset_[tile_id];

    std::get<0>(tuple)->DrawRectangle(position, *std::get<1>(tuple));
}

size_t TileSetPack::Size() { return tileset_.size(); }

float TileSetPack::GetTileWidth() { return tile_width_; }

float TileSetPack::GetTileHeight() { return tile_height_; }

}  // namespace Brutal
