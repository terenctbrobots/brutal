#include <fstream>
#include <vector>
#include "nlohmann/json.hpp"
using json = nlohmann::json;

#include "helper.h"
#include "sprite.h"

Sprite::Sprite() 
{

}

Sprite::~Sprite() 
{

}
/*
* Private
*/

/**
 * @brief load json metdata data for sprite, populate and create
 * 
 * @return int - enumerated success(0) or error codes (i.e.Graphics::ERROR_)
 */
int Sprite::LoadJSON() 
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

    if (json_data["width"] != nullptr) 
    {
        width = json_data["width"];
    } else {
        width = 32;
    }

    if (json_data["height"] != nullptr) 
    {
        height = json_data["height"];
    } else {
        height = 32;
    }

    animation_list_.clear();
    
    json animation_data = json_data["animation"];

    for (auto &animation : animation_data.items())
    {

//        std::cout << "key: " << el.key() << ", value: " << el.value() << '\n';
    }

    return Graphics::OK;
}


/*
* Public
*/

/**
 * @brief Loads a sprite sheet in to memory and reads a corresponding json meta data file(i.e. archer.jpg=>archer.json)
 * 
 * @param file_name 
 * @return int 
 */
int Sprite::Load(std::string const &file_name) 
{
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

void Sprite::Draw() 
{
    
}