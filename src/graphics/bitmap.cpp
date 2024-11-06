#include "bitmap.h"

#include "spdlog/spdlog.h"

using namespace Graphics;

Bitmap::Bitmap() {}

Bitmap::~Bitmap() {
    if (image_.data != NULL) {
        UnloadImage(image_);
    }

    if (texture_.id > 0) {
        UnloadTexture(texture_);
    }
}

int Bitmap::Load(std::string const& file_name) {
    image_ = LoadImage(file_name.c_str());

    if (image_.data == NULL) {
        spdlog::error("Bitmap : failed to load {}", file_name);
        return Render::ERROR_TEXTURE_LOAD;
    }

    return Render::OK;
};

void Bitmap::Draw(Vector2 const& position, int16_t tile_id) {
    if (texture_.id > 0) {
        DrawTextureV(texture_, position, WHITE);
        return;
    }

    texture_ = LoadTextureFromImage(image_);
}