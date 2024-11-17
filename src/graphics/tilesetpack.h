#pragma once

#include "tileset.h"

namespace Brutal {

class TileSetPack {
   private:
    std::vector<std::tuple<std::shared_ptr<TileSet>, Rectangle*>> tileset_;

    int current_tile_id_index_ = 1;
    float tile_width_;
    float tile_height_;

   public:
    TileSetPack();
    ~TileSetPack();

    // TODO: Do we need a interface to add external created tilesets?
    // void Add(std::shared_ptr<TileSet> tile_set);
    int Load(std::string const& filename);
    // int LoadJSON(json tile_set_json);

    void Deserialize(json const& json_data);

    void Draw(Vector2 const& position, uint16_t tile_id);
    size_t Size();
    float GetTileWidth();
    float GetTileHeight();
};

}  // namespace Brutal