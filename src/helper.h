#ifndef HELPER_H
#define HELPER_H
#include <cstdint>
#include <optional>
#include <string>

#include "raylib.h"

enum { LOAD_OK = 0, LOAD_FAIL };

std::optional<std::string> LoadTextFile(std::string const& filename);

uint64_t TimeMillisec();

Vector2 operator+(Vector2 lhs, Vector2 const& rhs);
Vector2 operator-(Vector2 lhs, Vector2 const& rhs);

constexpr size_t hash(const char* str) {
    const long long p = 131;
    const long long m = 4294967291;  // 2^32 - 5, largest 32 bit prime
    long long total = 0;
    long long current_multiplier = 1;
    for (int i = 0; str[i] != '\0'; ++i) {
        total = (total + current_multiplier * str[i]) % m;
        current_multiplier = (current_multiplier * p) % m;
    }
    return total;
}

#endif