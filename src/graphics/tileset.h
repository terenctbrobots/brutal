#ifndef TILESET_H
#define TILESET_H
#include <string>

#include "raylib.h"
#include "nlohmann/json.hpp"
using json = nlohmann::json;
#include "graphics.h"

class TileSet : public Graphics
{
    private:
        std::string json_filename_;
        Texture2D texture_;

    private:
        int LoadJSON();
        int ProcessJSON(json const& tile_json);
    public:
        uint width;
        uint height;

    public:
        TileSet();
        ~TileSet();

        int Load(std::string const& file_name);
        int Load(json tile_json);
};


#endif