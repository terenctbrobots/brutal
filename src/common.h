#ifndef COMMON_H_
#define COMMON_H_
#include <cstdint>
#include <entt/entt.hpp>
#include <string>

#include "raylib.h"
#include "spdlog/spdlog.h"

#define JSON_NOEXCEPTION
#include "nlohmann/json.hpp"
using json = nlohmann::json;

#endif