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

    sprite.width = json_data["width"];
    sprite.height = json_data["height"];

    sprite.animation_list.clear();

    json animation_list_json = json_data["animation"];

    float y = 0;

    for (auto& animation_json : animation_list_json.items()) {
        json frame_data = animation_json.value();

        Vector2 offset = {0, 0};

        if (frame_data["offsetX"] != nullptr) {
            offset.x = sprite.width * (double)frame_data["offsetX"];
        }

        if (frame_data["offsetY"] != nullptr) {
            offset.y = sprite.height * (double)frame_data["offsetY"];
        }

        auto animation = std::make_shared<SpriteAnimation>();
        animation->frame_rate = frame_data["frameRate"];
        animation->frames = frame_data["frames"];
        animation->width = sprite.width;
        animation->height = sprite.height;
        animation->offset = offset;

        for (int x_count = 0; x_count < animation->frames; x_count++) {
            float x = x_count * animation->width;
            animation->frame_list.push_back(
                std::unique_ptr<Rectangle>(new Rectangle{x, y, animation->width, animation->height}));
        }

        sprite.animation_list[animation_json.key()] = animation;

        y += sprite.height;
    }

    if (json_data["defaultAnimation"] != nullptr) {
        SetAnimation(sprite, json_data["defaultAnimation"]);
    }

    return sprite;
}

void Sprite::Draw(Vector2 const& position, SpriteComponent& sprite) {
    if (sprite.current_animation == nullptr) {
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
        sprite.next_draw_time = current_time + sprite.current_animation->frame_rate;
        sprite.current_frame++;
        if (sprite.current_frame == sprite.current_animation->frames) {
            sprite.current_frame = 0;
        }
    }

    Vector2 offset_position = position - sprite.current_animation->offset;
    DrawTextureRec(sprite.texture, *sprite.current_animation->frame_list[sprite.current_frame], offset_position, WHITE);
}
void Sprite::SetAnimation(SpriteComponent& sprite, std::string const& animation) {
    if (!sprite.animation_list[animation]) {
        return;
    }

    if (sprite.current_animation != nullptr) {
        ResetAnimation(sprite);
    }

    sprite.current_frame = 0;
    sprite.current_animation = sprite.animation_list[animation];
}

void Sprite::FlipAnimationX(SpriteComponent& sprite) {
    if (sprite.current_animation == nullptr) {
        return;
    }

    for (auto& rect_ptr : sprite.current_animation->frame_list) {
        rect_ptr->width *= -1;
    }
}

void Sprite::FlipAnimationY(SpriteComponent& sprite) {
    if (sprite.current_animation == nullptr) {
        return;
    }

    for (auto& rect_ptr : sprite.current_animation->frame_list) {
        rect_ptr->height *= -1;
    }
}

void Sprite::ResetAnimation(SpriteComponent& sprite) {
    if (sprite.current_animation == nullptr) {
        return;
    }

    for (auto& rect_ptr : sprite.current_animation->frame_list) {
        rect_ptr->width = sprite.width;
        rect_ptr->height = sprite.height;
    }
}

}  // namespace Brutal
