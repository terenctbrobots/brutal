#include "bitmap.h"

#include "spdlog/spdlog.h"

namespace Brutal
{
BitmapComponent Bitmap::Deserialize(json const& json_data)
{
    BitmapComponent bitmap;

    std::string filename = json_data["fileName"];
    bitmap.m_Image = LoadImage(filename.c_str());

    if (bitmap.m_Image.data == NULL)
    {
        spdlog::error("Bitmap : failed to load {}", filename);
        abort();
    }

    return bitmap;
}

void Bitmap::Draw(Vector2 const& position, BitmapComponent& bitmap)
{
    if (!bitmap.m_ConvertImage)
    {
        bitmap.m_Texture = LoadTextureFromImage(bitmap.m_Image);
        bitmap.m_ConvertImage = true;
    }

    DrawTextureV(bitmap.m_Texture, position, WHITE);
}

}  // namespace Brutal
