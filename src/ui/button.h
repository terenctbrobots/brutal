#ifndef BUTTON_H_
#define BUTTON_H_

#include "common.h"

namespace Brutal {

struct ButtonComponent {
    std::string text_field;  // TODO: Switch to better string class?
    float width;
    float height;
};

class Button {
   public:
    static ButtonComponent Deserialize(json const& json_data);
    static void Draw(Vector2 const& position, ButtonComponent& button);
};

}  // namespace Brutal

#endif