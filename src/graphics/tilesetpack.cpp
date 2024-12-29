#include "tilesetpack.h"

#include <iostream>

namespace Brutal
{

TileSetPack::TileSetPack() {}

TileSetPack::~TileSetPack() {}

void TileSetPack::Deserialize(json const& jsonData)
{
    // Tile_id 0 is a blank

    tileset_.push_back({nullptr, NULL});

    for (auto& tileset_data : jsonData)
    {
        auto tileset = std::make_shared<TileSet>();
        tileset->Deserialize(tileset_data);

        uint32_t tile_count = tileset->m_TileCount;

        for (int i = 0; i < tile_count; i++)
        {
            tileset_.push_back({tileset, &tileset->tile_list_[i]});
        }
        current_tile_id_index_ += tile_count;
#ifdef DEBUG
        spdlog::info("TileSetPack: {} tiles loaded", tile_count);
#endif
    }

    auto& tuple = tileset_[1];
    tile_width_ = std::get<0>(tuple)->m_TileWidth;
    tile_height_ = std::get<0>(tuple)->m_TileHeight;
}

void TileSetPack::Draw(Vector2 const& position, uint16_t tileId)
{
    if (tileId >= current_tile_id_index_ || tileId == 0)
    {
        spdlog::error("TileSetPack: trying to draw a unknown tile {}", tileId);
        abort();
    }

    auto& tuple = tileset_[tileId];

    std::get<0>(tuple)->DrawRectangle(position, *std::get<1>(tuple));
}

size_t TileSetPack::Size() { return tileset_.size(); }

float TileSetPack::GetTileWidth() { return tile_width_; }

float TileSetPack::GetTileHeight() { return tile_height_; }

}  // namespace Brutal
