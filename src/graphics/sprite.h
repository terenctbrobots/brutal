#ifndef SPRITE_H
#define SPRITE_H
#include <string>
#include "graphics.h"

class Sprite : public  Graphics {
    public:
        Sprite();
        ~Sprite();

        int Load(std::string const &file_name);
        void Draw();
};

#endif