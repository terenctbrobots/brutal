#include "sprite.h"

#include <fstream>
#include <iostream>
#include <memory>
#include <vector>

#include "helper.h"
#include "spdlog/spdlog.h"

namespace Brutal {
SpriteComponent Sprite::Deserialize(json const& json_data) {
    SpriteComponent sprite;

    std::string filename = json_data["fileName"];

    sprite.texture = LoadTexture(filename.c_str());
#ifdef DEBUG
    if (sprite.texture.id == 0) {
        spdlog::error("Sprite: could not load {} texture", filename);
        abort();
    }
#endif

    sprite.m_Width = json_data["width"];
    sprite.m_Height = json_data["height"];

    sprite.m_AnimationList.clear();

    json animation_list_json = json_data["animation"];

    float y = 0;

    for (auto& animation_json : animation_list_json.items()) {
        json frame_data = animation_json.value();

        Vector2 m_Offset = {0, 0};

        if (frame_data["offsetX"] != nullptr) {
            m_Offset.x = sprite.m_Width * (double)frame_data["offsetX"];
        }

        if (frame_data["offsetY"] != nullptr) {
            m_Offset.y = sprite.m_Height * (double)frame_data["offsetY"];
        }

        auto animation = std::make_shared<SpriteAnimation>();
        animation->m_FrameRate = frame_data["frameRate"];
        animation->m_Frames = frame_data["m_Frames"];
        animation->m_Width = sprite.m_Width;
        animation->m_Height = sprite.m_Height;
        animation->m_Offset = m_Offset;

        for (int x_count = 0; x_count < animation->m_Frames; x_count++) {
            float x = x_count * animation->m_Width;
            animation->frame_list.push_back(
                std::unique_ptr<Rectangle>(new Rectangle{x, y, animation->m_Width, animation->m_Height}));
        }

        sprite.m_AnimationList[animation_json.key()] = animation;

        y += sprite.m_Height;
    }

    if (json_data["defaultAnimation"] != nullptr) {
        SetAnimation(sprite, json_data["defaultAnimation"]);
    }

    return sprite;
}

void Sprite::Draw(Vector2 const& position, SpriteComponent& sprite) {
    if (sprite.m_CurrentAnimation == nullptr) {
        return;
    }

#ifdef DEBUG
    if (sprite.texture.id == 0) {
        spdlog::error("Sprite: No texture found");
        abort();
    }
#endif

    uint64_t current_time = TimeMillisec();

    if (sprite.next_draw_time == 0 || current_time >= sprite.next_draw_time) {
        sprite.next_draw_time = current_time + sprite.m_CurrentAnimation->m_FrameRate;
        sprite.m_CurrentFrame++;
        if (sprite.m_CurrentFrame == sprite.m_CurrentAnimation->m_Frames) {
            sprite.m_CurrentFrame = 0;
        }
    }

    Vector2 offset_position = position - sprite.m_CurrentAnimation->m_Offset;
    DrawTextureRec(sprite.texture, *sprite.m_CurrentAnimation->frame_list[sprite.m_CurrentFrame], offset_position, WHITE);
}
void Sprite::SetAnimation(SpriteComponent& sprite, std::string const& animation) {
    if (!sprite.m_AnimationList[animation]) {
        return;
    }

    if (sprite.m_CurrentAnimation != nullptr) {
        ResetAnimation(sprite);
    }

    sprite.m_CurrentFrame = 0;
    sprite.m_CurrentAnimation = sprite.m_AnimationList[animation];
}

void Sprite::FlipAnimationX(SpriteComponent& sprite) {
    if (sprite.m_CurrentAnimation == nullptr) {
        return;
    }

    for (auto& rect_ptr : sprite.m_CurrentAnimation->frame_list) {
        rect_ptr->width *= -1;
    }
}

void Sprite::FlipAnimationY(SpriteComponent& sprite) {
    if (sprite.m_CurrentAnimation == nullptr) {
        return;
    }

    for (auto& rect_ptr : sprite.m_CurrentAnimation->frame_list) {
        rect_ptr->height *= -1;
    }
}

void Sprite::ResetAnimation(SpriteComponent& sprite) {
    if (sprite.m_CurrentAnimation == nullptr) {
        return;
    }

    for (auto& rect_ptr : sprite.m_CurrentAnimation->frame_list) {
        rect_ptr->width = sprite.m_Width;
        rect_ptr->height = sprite.m_Height;
    }
}

}  // namespace Brutal
