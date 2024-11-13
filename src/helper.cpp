#include "helper.h"

#include <chrono>
#include <cstdint>
#include <fstream>
#include <iostream>

std::string GetJSONFilename(std::string const& file_name) {
    std::string return_string;

    // Scan from back to front to then copy remaining string
    for (auto it = file_name.end(); it != file_name.begin(); it--) {
        if (*it == '.') {
            for (auto copyit = file_name.begin(); copyit != it; copyit++) {
                return_string += *copyit;
            }
            break;
        }
    }

    if (return_string.length() > 0) {
        return_string += ".json";
    }

    return return_string;
}

// TODO: Not used, but can keep it here for other text files besides JSON
std::optional<std::string> LoadTextFile(std::string const& file_name) {
    std::ifstream file(file_name);

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
