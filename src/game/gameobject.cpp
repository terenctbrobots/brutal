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
    if (component.m_Image.data != NULL) {
        UnloadImage(component.m_Image);
        component.m_Image.data = NULL;
    }

    if (component.m_Texture.id > 0) {
        UnloadTexture(component.m_Texture);
        component.m_Texture.id = 0;
    }
}
}  // namespace Brutal
