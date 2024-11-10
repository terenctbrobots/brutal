#ifndef TILELAYER_H
#define TILELAYER_H

#include "common.h"
#include "layer.h"
#include "tilesetpack.h"

namespace Brutal {
class TileLayer : public Layer {
   private:
    std::shared_ptr<TileSetPack> tile_set_pack_;
    uint16_t* layer_data_;
    uint32_t width_;
    uint32_t height_;

    int32_t start_tile_x_;
    int32_t start_tile_y_;
    uint32_t end_tile_x_;
    uint32_t end_tile_y_;
    uint32_t draw_width_;
    uint32_t draw_height_;

    uint32_t tile_width_;
    uint32_t tile_height_;

    uint32_t layer_pixel_width_;
    uint32_t layer_pixel_height_;

    Vector2 draw_offset_;

   public:
    TileLayer(uint32_t width, uint32_t height);
    ~TileLayer();

    std::shared_ptr<TileSetPack> SetTileSetPack(std::shared_ptr<TileSetPack> tile_set_pack);
    void SetLayerData(json layer_data);

    void OrganizeDraw() override;
    void DrawTiles(uint32_t tile_x, uint32_t tile_y);
    void Draw() override;
};

}  // namespace Brutal

#endif