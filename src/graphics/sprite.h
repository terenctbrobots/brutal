#pragma once

#include "common.h"
#include "game/gameobject.h"
#include "raylib.h"

namespace Brutal
{
struct SpriteAnimation
{
    std::vector<std::unique_ptr<Rectangle>> frame_list;
    u_int m_FrameRate;
    u_int m_Frames;
    Vector2 m_Offset;
    float m_Width;
    float m_Height;
};

// TODO: Consider changing the rectangles to fixed arrays instead
struct SpriteComponent
{
    Texture2D texture = {0};

    u_int m_CurrentFrame;
    std::shared_ptr<SpriteAnimation> m_CurrentAnimation;
    u_int64_t next_draw_time = 0;
    //    Vector2 frame_offset;
    std::unordered_map<std::string, std::shared_ptr<SpriteAnimation>> m_AnimationList;

    uint32_t m_Width;
    uint32_t m_Height;
};

class Sprite
{
   public:
    static SpriteComponent Deserialize(json const& json_data);
    static void Draw(Vector2 const& position, SpriteComponent& sprite);
    static void SetAnimation(SpriteComponent& sprite, std::string const& animation);
    static void ResetAnimation(SpriteComponent& sprite);
    static void FlipAnimationX(SpriteComponent& sprite);
    static void FlipAnimationY(SpriteComponent& sprite);
};

}  // namespace Brutal