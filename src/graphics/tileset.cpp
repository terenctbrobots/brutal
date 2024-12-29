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
    std::string filename = json_data["image"];
    texture_ = LoadTexture(filename.c_str());

    if (texture_.id == 0) {
        spdlog::error("TileSet: could not load texture named {}", filename);
        abort();
    }
#ifdef DEBUG
    spdlog::info("TileSet: Loaded texture {}", filename);
#endif

    m_Width = json_data["imagewidth"];
    m_Height = json_data["imageheight"];

    m_TileWidth = json_data["tilewidth"];
    m_TileHeight = json_data["tileheight"];

    m_Name = json_data["name"];

    m_TileCount = json_data["tilecount"];

    float tile_x = 0;
    float tile_y = 0;

    for (int i = 0; i < m_TileCount; i++) {
        tile_list_.push_back({tile_x, tile_y, m_TileWidth, m_TileHeight});
        tile_x += m_TileWidth;

        if (tile_x >= m_Width) {
            tile_x = 0;
            tile_y += m_TileHeight;
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