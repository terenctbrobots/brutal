#pragma once

#include <string>

#include "UUID.h"

namespace Brutal
{
struct IDComponent
{
    UUID m_ID;

    IDComponent() = default;
    IDComponent(const IDComponent&) = default;
};

struct TagComponent
{
    std::string m_Tag;

    TagComponent() = default;
    TagComponent(const TagComponent&) = default;
    TagComponent(const std::string& tag) : m_Tag(tag) {}
};

struct LayerComponent
{
    int m_Layer;
};

struct ScriptComponent
{
    std::string m_Filename;
    bool m_OnTick = false;
};

}  // namespace Brutal