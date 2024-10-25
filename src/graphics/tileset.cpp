#include <fstream>
#include "helper.h"
#include "tileset.h"

/*
* Private
*/

int TileSet::LoadJSON() 
{
    std::ifstream json_file(json_filename_);

    if (!json_file.good()) 
    {
        return Graphics::ERROR_JSON_LOAD;
    }

    json json_data = json::parse(json_file,nullptr,false);

    if (json_data == nullptr) 
    {
        return Graphics::ERROR_JSON_LOAD;
    }

    ProcessJSON(json_data);

    return Graphics::OK;
}

int TileSet::ProcessJSON(json const& tile_json)
{
    return Graphics::OK;
}

/*
* Public
*/
int TileSet::Load(std::string const& file_name) 
{
    texture_ = LoadTexture(file_name.c_str());

    if (texture_.id == 0) 
    {
        return Graphics::ERROR_TEXTURE_LOAD;   
    }

    json_filename_ = GetJSONFilename(file_name);

    if (json_filename_.length() == 0) {
        return Graphics::ERROR_JSON_FILENAME;
    }

    int return_value = LoadJSON(); 

    if ( return_value != Graphics::OK) {
        return return_value;
    }

    return Graphics::OK;
}