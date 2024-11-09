#ifndef SPRITE_H
#define SPRITE_H
#include <string>

#include "game/gameobject.h"
#include "nlohmann/json.hpp"
#include "raylib.h"
#include "render.h"

using json = nlohmann::json;

struct SpriteAnimation {
    std::vector<std::unique_ptr<Rectangle>> frame_list;
    u_int frame_rate;
    u_int frames;
    Vector2 offset;
    float width;
    float height;
};

// TODO: Consider changing the pts to fixed arrays instead
struct SpriteComponent {
    Texture2D texture = {0, 0, 0, 0, 0};

    u_int current_frame;
    std::shared_ptr<SpriteAnimation> current_animation;
    u_int64_t next_draw_time;
    Vector2 frame_offset;
    std::unordered_map<std::string, std::shared_ptr<SpriteAnimation>> animation_list;

    uint32_t width;
    uint32_t height;
};

class Sprite {
   public:
    static void Deserialize(SpriteComponent& sprite, GameObject& gameobject, json const& json_data);
    static void Draw(Vector2 const& position, SpriteComponent& sprite);
    static void SetAnimation(SpriteComponent& sprite, std::string const& animation);
    static void ResetAnimation(SpriteComponent& sprite);
    static void FlipAnimationX(SpriteComponent& sprite);
    static void FlipAnimationY(SpriteComponent& sprite);
};
#endif