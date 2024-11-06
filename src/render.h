#ifndef RENDER_H
#define RENDER_H

#include <cstdint>

#include "nlohmann/json.hpp"
#include "raylib.h"
using json = nlohmann::json;

class Render {
   public:
    enum ReturnType {
        OK = 0,
        ERROR_JSON_FILENAME,
        ERROR_JSON_LOAD,
        ERROR_JSON,
        ERROR_TEXTURE_LOAD,
        ERROR_GRAPHIC_LAST,
    };
    virtual void Draw(Vector2 const& position, int16_t tile_id = 0) = 0;
    virtual int Load(std::string const& file_name) = 0;

    virtual int DeSerialize(json const& json_data) = 0;
};

#endif