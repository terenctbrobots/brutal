#ifndef GRAPHICS_H
#define GRAPHICS_H

#include <cstdint>

class Graphics 
{
    public:
        enum ReturnType 
        {
            OK = 0,
            ERROR_JSON_FILENAME,
            ERROR_JSON_LOAD,
            ERROR_JSON,
            ERROR_TEXTURE_LOAD,
            ERROR_GRAPHIC_LAST,
        };
        virtual void Draw(Vector2 const& position,int16_t tile_id = 0) = 0;
        virtual int Load(std::string const& file_name) = 0;
};

#endif