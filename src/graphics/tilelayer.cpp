#include "tilelayer.h"

/**
 * @brief Construct a new Tile Layer:: Tile Layer object
 * 
 * @param width number of tiles in the x direction in entire layer
 * @param height number of tiles in the y direction in entire layer
 * @param draw_width number of tiles to draw in the x direction <= width
 * @param draw_height number of tiles to draw in the y direction <= height
 */
TileLayer::TileLayer(uint32_t width, uint32_t height, uint32_t draw_width, uint32_t draw_height)
{
    tile_set_pack_ = nullptr;
    layer_data_ = new uint16_t[width * height];
    width_ = width;
    height_ = height;

    draw_width_ = draw_width;
    draw_height_ = draw_height;

    draw_offset = {0,0};
}

TileLayer::~TileLayer()
{
    if (layer_data_) 
    {
        delete[] layer_data_;
    }
}

void TileLayer::SetTileSetPack(std::shared_ptr<TileSetPack> tile_set_pack)
{
    tile_set_pack_ = tile_set_pack;

    tile_width_ = tile_set_pack_->GetTileWidth();
    tile_height_ = tile_set_pack_->GetTileHeight();
}

void TileLayer::SetLayerData(json layer_data) 
{
    uint16_t x,y = 0;

    for (auto& el: layer_data.items())
    {
        layer_data_[y*width_ + x] = el.value();

        x++;

        if (x==width_) 
        {
            x = 0;
            y++;
        }
    }
}

/**
 * @brief draw to screen tile later data starting with tile_x and tile_y until number of tiles in draw_width and height
 * 
 * @param tile_x 
 * @param tile_y 
 */
void TileLayer::Draw(uint32_t tile_x, uint32_t tile_y)
{
    if (tile_set_pack_ == nullptr || tile_set_pack_->Size() == 0)
    {
        return;
    }

    uint32_t tile_x_end = tile_x + draw_width_;
    if (tile_x_end > width_)
    {
        tile_x_end = width_;
    }

    uint32_t tile_y_end = tile_y + draw_height_;
    if (tile_y_end > height_)
    {
        tile_y_end = height_;
    }

    Vector2 position = {0,0};

    for (uint32_t draw_y=tile_y; draw_y < tile_y_end; draw_y++)
    {
        for (uint32_t draw_x=tile_x; draw_x < tile_x_end; draw_x++)
        {
            uint16_t tile_id = layer_data_[draw_y*width_ + draw_x];
            tile_set_pack_->Draw(position, tile_id);

            position.x += tile_width_;
        }

        position.x = 0;
        position.y += tile_height_;
    }

}