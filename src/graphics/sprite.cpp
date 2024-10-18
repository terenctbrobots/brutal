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
    //TODO: Move this into a base class later? or helper function
    std::ifstream file(m_json_filename);

    if (!file) 
    {
        return Graphics::ERROR_JSON_LOAD;
    }

    file.seekg(0, std::ios::end);
    std::streampos length = file.tellg();
    file.seekg(0, std::ios::beg);

    std::vector<char> buffer;
    buffer.resize(length);
    file.read(&buffer[0], length);

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