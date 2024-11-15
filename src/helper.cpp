#include "helper.h"

#include <chrono>
#include <cstdint>
#include <fstream>
#include <iostream>

// TODO: Not used, but can keep it here for other text files besides JSON
std::optional<std::string> LoadTextFile(std::string const& filename) {
    std::ifstream file(filename);

    if (!file.good()) {
        return std::nullopt;
    }

    std::string file_contents((std::istreambuf_iterator<char>(file)), std::istreambuf_iterator<char>());

    return file_contents;
}

uint64_t TimeMillisec() {
    using namespace std::chrono;
    return duration_cast<milliseconds>(system_clock::now().time_since_epoch()).count();
}

Vector2 operator+(Vector2 lhs, Vector2 const& rhs) {
    lhs.x += rhs.x;
    lhs.y += rhs.y;

    return lhs;
};

Vector2 operator-(Vector2 lhs, Vector2 const& rhs) {
    lhs.x -= rhs.x;
    lhs.y -= rhs.y;

    return lhs;
};
