#ifndef BITMAP_H_
#define BITMAP_H_

#include "common.h"
#include "game/gameobject.h"
#include "raylib.h"

namespace Brutal {
struct BitmapComponent {
    Image image = {NULL};
    Texture texture = {0};
    bool convert_image = false;
};

class Bitmap {
   public:
    static BitmapComponent Deserialize(json const& json_data);
    static void Draw(Vector2 const& position, BitmapComponent& bitmap);
};

}  // namespace Brutal

#endif