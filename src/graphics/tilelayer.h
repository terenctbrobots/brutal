#ifndef TILELAYER_H
#define TILELAYER_H

#include "layer.h"
#include "tilesetpack.h"

class TileLayer : public Layer 
{
    private:
        std::shared_ptr<TileSetPack> tile_set_pack_;
        uint16_t* layer_data_;
        uint32_t width_;
        uint32_t height_;

        uint32_t draw_width_;
        uint32_t draw_height_;

        uint32_t tile_width_;
        uint32_t tile_height_;

    public:
        //TODO: Move this to a shared struct later?
        Vector2 draw_offset;

        TileLayer(uint32_t width, uint32_t height,uint32_t tile_draw_width, uint32_t tile_draw_height);
        ~TileLayer();

        void SetTileSetPack(std::shared_ptr<TileSetPack> tile_set_pack);
        void SetLayerData(json layer_data);

        void Draw(uint32_t tile_x, uint32_t tile_y);
};


#endif