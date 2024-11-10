#include "gameobject.h"

#include <iostream>

#include "game/game.h"
#include "graphics/bitmap.h"
#include "graphics/sprite.h"
#include "helper.h"

namespace Brutal {
GameObject::GameObject(entt::entity handle, Level *level) : handle_(handle), level_(level) {}

GameObject::~GameObject() {
    if (HasComponent<SpriteComponent>()) {
        auto &sprite_component = GetComponent<SpriteComponent>();
        if (sprite_component.texture.id > 0) {
            UnloadTexture(sprite_component.texture);
        }
    }

    if (HasComponent<BitmapComponent>()) {
        auto &bitmap_component = GetComponent<BitmapComponent>();
        if (bitmap_component.image.data != NULL) {
            UnloadImage(bitmap_component.image);
        }

        if (bitmap_component.texture.id > 0) {
            UnloadTexture(bitmap_component.texture);
        }
    }
}
template <typename T>
void GameObject::OnComponentAdd(T &component) {
    static_assert(sizeof(T) == 0);
}

template <>
void GameObject::OnComponentAdd<SpriteComponent>(SpriteComponent &component) {
    auto &rectangle = GetComponent<Rectangle>();
    rectangle.width = component.width;
    rectangle.height = component.height;
}

template <typename T>
void GameObject::OnComponentRemove(T &component) {
    static_assert(sizeof(T) == 0);
}

template <>
void GameObject::OnComponentRemove<SpriteComponent>(SpriteComponent &component) {
    if (component.texture.id > 0) {
        UnloadTexture(component.texture);
    }
}

template <>
void GameObject::OnComponentRemove<BitmapComponent>(BitmapComponent &component) {
    if (component.image.data != NULL) {
        UnloadImage(component.image);
    }

    if (component.texture.id > 0) {
        UnloadTexture(component.texture);
    }
}
}  // namespace Brutal
