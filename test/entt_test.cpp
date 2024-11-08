#include <gtest/gtest.h>

#include <entt/entt.hpp>
#include <iostream>
#include <memory>
#include <string_view>

namespace {

struct position {
    float x;
    float y;
};

struct velocity {
    float dx;
    float dy;
};

TEST(ENTTTest, TestBasicENTT) {
    entt::registry registry;

    for (auto i = 0u; i < 10u; ++i) {
        const auto entity = registry.create();
        registry.emplace<position>(entity, i * 1.f, i * 1.f);
        if (i % 2 == 0) {
            registry.emplace<velocity>(entity, i * .1f, i * .1f);
        }
    }
}
}  // namespace
