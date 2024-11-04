#include "tilelayer.h"

#include "game/game.h"
#include "spdlog/spdlog.h"

/**
 * @brief Construct a new Tile Layer:: Tile Layer object
 *
 * @param width number of tiles in the x direction in entire layer
 * @param height number of tiles in the y direction in entire layer
 */
TileLayer::TileLayer(uint32_t width, uint32_t height) {
    tile_set_pack_ = nullptr;
    layer_data_ = new uint16_t[width * height];
    width_ = width;
    height_ = height;

    draw_offset_ = {0, 0};

    layer_type_ = Layer::TILE;
}

TileLayer::~TileLayer() {
    if (layer_data_) {
        delete[] layer_data_;
    }
}

std::shared_ptr<TileSetPack> TileLayer::SetTileSetPack(std::shared_ptr<TileSetPack> tile_set_pack) {
    tile_set_pack_ = tile_set_pack;

    tile_width_ = tile_set_pack_->GetTileWidth();
    tile_height_ = tile_set_pack_->GetTileHeight();

    Game& game = Game::Get();

    draw_width_ = std::round(game.view_screen.width / tile_width_) + 1;

    if (draw_width_ > width_) {
        draw_width_ = width_;
    }

    draw_height_ = std::round(game.view_screen.height / tile_height_) + 1;

    if (draw_height_ > height_) {
        draw_height_ = height_;
    }

    layer_pixel_width_ = tile_width_ * width_;
    layer_pixel_height_ = tile_height_ * height_;

#ifdef DEBUG
    spdlog::info("TileLayer : tile width {} & height {}, draw width {} & height {} pixel width {} & height {}",
                 tile_width_, tile_height_, draw_width_, draw_height_, layer_pixel_width_, layer_pixel_height_);
#endif
    return tile_set_pack_;
}

void TileLayer::SetLayerData(json layer_data) {
    uint16_t x, y = 0;

    for (auto& el : layer_data.items()) {
        layer_data_[y * width_ + x] = el.value();

        x++;

        if (x == width_) {
            x = 0;
            y++;
        }
    }
}

void TileLayer::OrganizeDraw() {
    Game& game = Game::Get();

    if (game.view_screen.x < 0) {
        draw_offset_.x = abs(game.view_screen.x);

        if (draw_offset_.x > layer_pixel_width_) {
            start_tile_x_ = -1;
            return;
        } else {
            start_tile_x_ = 0;
        }
    } else {
        start_tile_x_ = std::floor(game.view_screen.x / tile_width_);

        if (start_tile_x_ >= width_) {
            start_tile_x_ = -1;
        }
    }

    if (game.view_screen.y < 0) {
        draw_offset_.y = abs(game.view_screen.y);

        if (draw_offset_.y > layer_pixel_height_) {
            start_tile_y_ = -1;
            return;
        } else {
            start_tile_y_ = 0;
        }
    } else {
        start_tile_y_ = std::floor(game.view_screen.y / tile_width_);

        if (start_tile_y_ >= width_) {
            start_tile_y_ = -1;
            return;
        }
    }
}

void TileLayer::Draw() {
    if (start_tile_x_ == -1 || start_tile_y_ == -1) {
        return;
    }

    Vector2 position = draw_offset_;

    u_int32_t end_tile_x = start_tile_x_ + draw_width_;
    u_int32_t end_tile_y = start_tile_y_ + draw_height_;

    for (uint32_t tile_y = start_tile_y_; tile_y < end_tile_y; tile_y++) {
        for (uint32_t tile_x = start_tile_x_; tile_x < end_tile_x; tile_x++) {
            uint16_t tile_id = layer_data_[tile_y * width_ + tile_x];

            if (tile_id != 0) {
                tile_set_pack_->Draw(position, tile_id);
            }
            position.x += tile_width_;
        }
        position.y += tile_height_;
        position.x = draw_offset_.x;
    }
}

/**
 * @brief draw to screen tile later data starting with tile_x and tile_y
 * until number of tiles in draw_width and height
 *
 * @param tile_x
 * @param tile_y
 */
void TileLayer::DrawTiles(uint32_t tile_x, uint32_t tile_y) {
    if (tile_set_pack_ == nullptr || tile_set_pack_->Size() == 0) {
        return;
    }

    uint32_t tile_x_end = tile_x + draw_width_;
    if (tile_x_end > width_) {
        tile_x_end = width_;
    }

    uint32_t tile_y_end = tile_y + draw_height_;
    if (tile_y_end > height_) {
        tile_y_end = height_;
    }

    Vector2 position = {0, 0};

    for (uint32_t draw_y = tile_y; draw_y < tile_y_end; draw_y++) {
        for (uint32_t draw_x = tile_x; draw_x < tile_x_end; draw_x++) {
            uint16_t tile_id = layer_data_[draw_y * width_ + draw_x];
            tile_set_pack_->Draw(position, tile_id);

            position.x += tile_width_;
        }

        position.x = 0;
        position.y += tile_height_;
    }
}