#ifndef SPRITE_H
#define SPRITE_H
#include <string>
#include "graphics.h"

class Sprite : public  Graphics {
    private:
        std::string m_json_filename;

        int LoadJSON();
    public:
        Sprite();
        ~Sprite();

        int Load(std::string const &file_name);
        void Draw() override;
};

#endif