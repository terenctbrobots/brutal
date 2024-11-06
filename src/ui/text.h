#ifndef TEXT_H_
#define TEXT_H_

#include "render.h"

namespace UI {
class Text : Render {
   public:
    std::string text_field;  // Switch to better string class?
    int font_size = 20;

   public:
    Text();
    ~Text();

    int Load(std::string const& file_name) override;
    void Draw(Vector2 const& position, int16_t tile_id = 0) override;

    int DeSerialize(json const& json_data) override;
};
}  // namespace  UI

#endif