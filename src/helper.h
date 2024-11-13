#ifndef HELPER_H
#define HELPER_H
#include <cstdint>
#include <optional>
#include <string>

#include "raylib.h"

std::string GetJSONFilename(std::string const& file_name);

enum { LOAD_OK = 0, LOAD_FAIL };

std::optional<std::string> LoadTextFile(std::string const& file_name);

uint64_t TimeMillisec();

Vector2 operator+(Vector2 lhs, Vector2 const& rhs);
Vector2 operator-(Vector2 lhs, Vector2 const& rhs);

#endif