#pragma once

#include "graphics/tileset.h"

namespace Brutal
{

class TileSetPack
{
   private:
    std::vector<std::tuple<std::shared_ptr<TileSet>, Rectangle*>> tileset_;

    int current_tile_id_index_ = 1;
    float tile_width_;
    float tile_height_;

   public:
    TileSetPack();
    ~TileSetPack();

    void Deserialize(json const& jsonData);

    void Draw(Vector2 const& position, uint16_t tileId);
    size_t Size();
    float GetTileWidth();
    float GetTileHeight();
};

}  // namespace Brutal