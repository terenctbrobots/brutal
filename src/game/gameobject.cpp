#include "gameobject.h"

#include <iostream>

#include "game/game.h"
#include "graphics/bitmap.h"
#include "graphics/sprite.h"
#include "helper.h"

namespace Brutal {
GameObject::GameObject(entt::entity handle, Level *level) : handle_(handle), level_(level) {}

GameObject::~GameObject() {}
template <typename T>
void GameObject::OnComponentAdd(T &component) {
    static_assert(sizeof(T) == 0);
}

// TODO: Not sure if this magic solution is the best, maybe let the editor handle it?
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
        component.texture.id = 0;
    }
}

template <>
void GameObject::OnComponentRemove<BitmapComponent>(BitmapComponent &component) {
    if (component.image.data != NULL) {
        UnloadImage(component.image);
        component.image.data = NULL;
    }

    if (component.texture.id > 0) {
        UnloadTexture(component.texture);
        component.texture.id = 0;
    }
}
}  // namespace Brutal
