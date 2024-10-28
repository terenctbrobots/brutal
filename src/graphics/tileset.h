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

        std::vector<std::unique_ptr<Rectangle>> tile_list_;

    private:
        int LoadJSON();
        int ProcessJSON(json const& tile_json);
    public:
        uint width;
        uint height;

        uint tile_width;
        uint tile_height;

        uint tile_count;
        uint tile_first_id;
        uint tile_last_id;

        std::string name;

    public:
        TileSet();
        ~TileSet();

        int Load(std::string const& file_name);

        void Draw(Vector2 const& position, uint tile_id = 0) override;
};


#endif