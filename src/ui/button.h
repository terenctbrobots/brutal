#ifndef BUTTON_H_
#define BUTTON_H_

#include "render.h"

namespace UI {

class Button : public Render {
   public:
    std::string text_field;  // TODO: Switch to better string class?
    float width;
    float height;

   public:
    Button();
    ~Button();

    int Load(std::string const& file_name) override;
    void Draw(Vector2 const& position) override;

    int DeSerialize(json const& json_data) override;
};

}  // namespace UI

#endif