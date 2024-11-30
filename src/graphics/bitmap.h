#pragma once

#include "common.h"
#include "game/gameobject.h"
#include "raylib.h"

namespace Brutal
{
struct BitmapComponent
{
    Image m_Image = {NULL};
    Texture m_Texture = {0};
    bool m_ConvertImage = false;
};

class Bitmap
{
   public:
    static BitmapComponent Deserialize(json const& json_data);
    static void Draw(Vector2 const& position, BitmapComponent& bitmap);
};

}  // namespace Brutal
