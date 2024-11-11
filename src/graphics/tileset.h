#ifndef TILESET_H
#define TILESET_H

#include "common.h"
#include "raylib.h"

namespace Brutal {
class TileSet {
   private:
    std::string json_filename_;
    Texture2D texture_;

    std::vector<std::unique_ptr<Rectangle>> tile_list_;

   private:
    int LoadJSON();

   public:
    uint32_t width;
    uint32_t height;

    uint32_t tile_width;
    uint32_t tile_height;

    uint32_t tile_count;
    int32_t tile_first_id;
    int32_t tile_last_id;

    std::string name;

   public:
    TileSet();
    ~TileSet();

    int Deserialize(json const& json_data);

    void Draw(Vector2 const& position, int16_t tile_id = 0);
};

}  // namespace Brutal

#endif