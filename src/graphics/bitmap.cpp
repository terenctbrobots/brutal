#include "bitmap.h"

#include "spdlog/spdlog.h"

namespace Brutal {
BitmapComponent Bitmap::Deserialize(json const& json_data) {
    BitmapComponent bitmap;

    std::string filename = json_data["fileName"];
    bitmap.image = LoadImage(filename.c_str());

    if (bitmap.image.data == NULL) {
        spdlog::error("Bitmap : failed to load {}", filename);
        abort();
    }

    return bitmap;
}

void Bitmap::Draw(Vector2 const& position, BitmapComponent& bitmap) {
    if (!bitmap.convert_image) {
        bitmap.texture = LoadTextureFromImage(bitmap.image);
        bitmap.convert_image = true;
    }

    DrawTextureV(bitmap.texture, position, WHITE);
}

}  // namespace Brutal
