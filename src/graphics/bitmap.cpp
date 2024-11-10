#include "bitmap.h"

#include "spdlog/spdlog.h"

namespace Brutal {
BitmapComponent Bitmap::Deserialize(json const& json_data) {
    BitmapComponent bitmap;

    std::string file_name = json_data["fileName"];
    bitmap.image = LoadImage(file_name.c_str());

    if (bitmap.image.data == NULL) {
        spdlog::error("Bitmap : failed to load {}", file_name);
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
