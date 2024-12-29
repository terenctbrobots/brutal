#pragma once

#include "common.h"
#include "raylib.h"

namespace Brutal
{

struct ButtonComponent
{
    std::string m_TextField;  // TODO: Switch to better string class? or string view?
    float m_Width;
    float m_Height;
};

class Button
{
   public:
    static ButtonComponent Deserialize(json const& json_data);
    static void Draw(Vector2 const& position, ButtonComponent& button, u_int64_t uuid);
};

}  // namespace Brutal