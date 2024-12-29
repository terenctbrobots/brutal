#include "gameobject.h"

#include <iostream>

#include "game/game.h"
#include "graphics/bitmap.h"
#include "graphics/sprite.h"
#include "helper.h"

namespace Brutal
{
GameObject::GameObject(entt::entity handle, Level *level) : handle_(handle), level_(level) {}

GameObject::~GameObject() {}
}  // namespace Brutal
