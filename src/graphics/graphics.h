#ifndef GRAPHICS_H
#define GRAPHICS_H

class Graphics 
{
    public:
        enum ReturnType 
        {
            OK = 0,
            ERROR_JSON_FILENAME,
            ERROR_JSON_LOAD,
            ERROR_TEXTURE_LOAD,
            ERROR_GRAPHIC_LAST,
        };
        virtual void Draw(Vector2 const &position) = 0;
};


#endif