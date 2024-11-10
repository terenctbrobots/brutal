#include <gtest/gtest.h>

#include <entt/entt.hpp>
#include <iostream>
#include <memory>
#include <string_view>

#include "graphics/sprite.h"

using namespace Brutal;

namespace {

TEST(ENTTTest, TestBasicENTT) {
    entt::registry registry;

    for (auto i = 0u; i < 10u; ++i) {
        const auto entity = registry.create();
        registry.emplace<SpriteComponent>(entity);
    }
}
}  // namespace
