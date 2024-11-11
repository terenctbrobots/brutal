#include "tilesetpack.h"

using namespace Brutal;

TileSetPack::TileSetPack() {}

TileSetPack::~TileSetPack() {}

int TileSetPack::Load(std::string const& file_name) {
    // std::shared_ptr<TileSet> new_tileset = std::make_shared<TileSet>();

    // int ret_value = new_tileset->Load(file_name);

    // if (ret_value != 0) {
    //     return ret_value;
    // }

    // new_tileset->tile_first_id = current_tile_id_index_;
    // new_tileset->tile_last_id = new_tileset->tile_first_id + new_tileset->tile_count;

    // for (int i = 0; i < new_tileset->tile_count; i++) {
    //     tileset_list_.push_back(new_tileset);
    // }

    // current_tile_id_index_ += new_tileset->tile_count;

    return 0;
}

void TileSetPack::Deserialize(json const& json_data) {
    for (auto& tileset : json_data) {
        std::shared_ptr<TileSet> new_tileset = std::make_shared<TileSet>();
        new_tileset->Deserialize(tileset);
        new_tileset->tile_first_id = current_tile_id_index_;
        new_tileset->tile_last_id = new_tileset->tile_first_id + new_tileset->tile_count;

        tileset_list_.push_back(new_tileset);
        current_tile_id_index_ += new_tileset->tile_count;
#ifdef DEBUG
        spdlog::info("TileSetPack: {} tiles loaded", new_tileset->tile_count);
#endif
    }
}

void TileSetPack::Draw(Vector2 const& position, uint16_t tile_id) {
    if (tile_id >= current_tile_id_index_) {
        spdlog::error("TileSetPack: Try to draw a unknown tile {}", tile_id);
        abort();
    }

    tileset_list_[0]->Draw(position, tile_id);
}

size_t TileSetPack::Size() { return tileset_list_.size(); }

uint32_t TileSetPack::GetTileWidth() {
    if (tileset_list_.size() == 0) {
        return 0;
    }

    return tileset_list_[0]->tile_width;
}

uint32_t TileSetPack::GetTileHeight() {
    if (tileset_list_.size() == 0) {
        return 0;
    }

    return tileset_list_[0]->tile_height;
}