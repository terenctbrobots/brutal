#ifndef TILESET_H
#define TILESET_H

#include "common.h"
#include "raylib.h"

namespace Brutal {
class TileSet {
   private:
    std::string json_filename_;
    Texture2D texture_;

    std::vector<Rectangle> tile_list_;

   private:
    int LoadJSON();

   public:
    uint32_t width;
    uint32_t height;

    float tile_width;
    float tile_height;

    uint32_t tile_count;

    std::string name;

   public:
    TileSet();
    ~TileSet();

    int Deserialize(json const& json_data);

    void DrawRectangle(Vector2 const& position, Rectangle const& rectangle);
    void Draw(Vector2 const& position, uint16_t tile_id);

    friend class TileSetPack;
};

}  // namespace Brutal

#endif