#pragma once

#include "common.h"
#include "raylib.h"

namespace Brutal
{
class TileSet
{
   private:
    std::string json_filename_;
    Texture2D texture_;

    std::vector<Rectangle> tile_list_;

   private:
    int LoadJSON();

   public:
    uint32_t m_Width;
    uint32_t m_Height;

    float m_TileWidth;
    float m_TileHeight;

    uint32_t m_TileCount;

    std::string m_Name;

   public:
    TileSet();
    ~TileSet();

    int Deserialize(json const& json_data);

    void DrawRectangle(Vector2 const& position, Rectangle const& rectangle);
    void Draw(Vector2 const& position, uint16_t tile_id);

    friend class TileSetPack;
};

}  // namespace Brutal