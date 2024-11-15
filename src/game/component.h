#pragma once 

#include <string>

#include "UUID.h"

namespace Brutal {
struct IDComponent {
    UUID ID;

    IDComponent() = default;
    IDComponent(const IDComponent&) = default;
};

struct TagComponent {
    std::string tag;

    TagComponent() = default;
    TagComponent(const TagComponent&) = default;
    TagComponent(const std::string& tag) : tag(tag) {}
};

struct LayerComponent {
    int layer;
};

struct ScriptComponent {
    std::string filename;
    bool on_tick = false;
};

}  // namespace Brutal