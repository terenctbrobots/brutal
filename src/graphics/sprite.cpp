#include <fstream>
#include <vector>
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

int Sprite::LoadJSON() 
{
    std::optional<std::string> text_buffer = LoadTextFile(m_json_filename);

    if (text_buffer == std::nullopt) 
    {
        return Graphics::ERROR_JSON_LOAD;
    }

    return Graphics::OK;
}


/*
* Public
*/
int Sprite::Load(std::string const &file_name) 
{
    m_json_filename = GetJSONFilename(file_name);

    if (m_json_filename.length() == 0) {
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