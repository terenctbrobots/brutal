#ifndef BITMAP_H_
#define BITMAP_H_

#include "raylib.h"
#include "render.h"

namespace Graphics {
class Bitmap : public Render {
   private:
    Image image_;

   public:
    Bitmap();
    ~Bitmap();

    int Load(std::string const& file_name) override;
    void Draw(Vector2 const& position, int16_t tile_id = 0) override;
};

}  // namespace Graphics

#endif