#include "tileset.h"

#include <fstream>

#include "helper.h"

using namespace Graphics;

TileSet::TileSet() { 
    tile_first_id = 1;
    texture_.id = 0;
}

TileSet::~TileSet() {
    if (texture_.id > 0) {
        UnloadTexture(texture_);
    }
}

/*
 * Private
 */

int TileSet::LoadJSON() {
    std::ifstream json_file(json_filename_);

    if (!json_file.good()) {
        return Render::ERROR_JSON_LOAD;
    }

    json json_data = json::parse(json_file, nullptr, false);

    if (json_data.is_discarded()) {
        return Render::ERROR_JSON_LOAD;
    }

    DeSerialize(json_data);

    return Render::OK;
}

int TileSet::DeSerialize(json const& json_data) {
    width = json_data["imagewidth"];
    height = json_data["imageheight"];

    tile_width = json_data["tilewidth"];
    tile_height = json_data["tileheight"];

    name = json_data["name"];

    tile_count = json_data["tilecount"];

    float tile_x, tile_y = 0;

    for (int i = 0; i < tile_count; i++) {
        tile_list_.push_back(
            std::unique_ptr<Rectangle>(new Rectangle{tile_x, tile_y, (float)tile_width, (float)tile_height}));
        tile_x += tile_width;

        if (tile_x >= width) {
            tile_x = 0;
            tile_y += tile_height;
        }
    }

    return Render::OK;
}

/*
 * Public
 */
int TileSet::Load(std::string const& file_name) {
    texture_ = LoadTexture(file_name.c_str());

    if (texture_.id == 0) {
        return Render::ERROR_TEXTURE_LOAD;
    }

    json_filename_ = GetJSONFilename(file_name);

    if (json_filename_.length() == 0) {
        return Render::ERROR_JSON_FILENAME;
    }

    int return_value = LoadJSON();

    if (return_value != Render::OK) {
        return return_value;
    }

    return Render::OK;
}

void TileSet::Draw(Vector2 const& position, int16_t tile_id) {
    int32_t offset_tile_id = tile_id - tile_first_id;

    if (offset_tile_id < 0 || offset_tile_id >= tile_count) {
        return;
    }

    DrawTextureRec(texture_, *tile_list_[offset_tile_id], position, WHITE);
}