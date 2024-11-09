#ifndef COMPONENT_H_
#define COMPONENT_H_

#include <string>

#include "UUID.h"

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

#endif