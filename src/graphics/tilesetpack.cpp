#include "tilesetpack.h"

TileSetPack::TileSetPack() {}

TileSetPack::~TileSetPack() {}

int TileSetPack::Load(std::string const& file_name) {
    std::shared_ptr<TileSet> new_tileset = std::make_shared<TileSet>();

    int ret_value = new_tileset->Load(file_name);

    if (ret_value != Render::OK) {
        return ret_value;
    }

    new_tileset->tile_first_id = current_tile_id_index_;
    new_tileset->tile_last_id = new_tileset->tile_first_id + new_tileset->tile_count;

    for (int i = 0; i < new_tileset->tile_count; i++) {
        tileset_list_.push_back(new_tileset);
    }

    current_tile_id_index_ += new_tileset->tile_count;

    return Render::OK;
}

void TileSetPack::Draw(Vector2 const& position, uint16_t tile_id) {
    if (tile_id > current_tile_id_index_) {
        return;
    }

    tileset_list_[tile_id]->Draw(position, tile_id);
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