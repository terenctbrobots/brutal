#ifndef BITMAP_H_
#define BITMAP_H_

#include "raylib.h"
#include "render.h"

namespace Graphics {
class Bitmap : public Render {
   private:
    Image image_;
    Texture texture_;

   public:
    Bitmap();
    ~Bitmap();

    int Load(std::string const& file_name) override;
    void Draw(Vector2 const& position) override;
    int DeSerialize(json const& json_data) override;
};

}  // namespace Graphics

#endif