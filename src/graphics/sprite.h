#ifndef SPRITE_H
#define SPRITE_H
#include <string>
#include "graphics.h"

//TODO: Do we need to convert this to u_int16?
struct Animation 
{
    u_int x1;
    u_int x2;
    u_int y1;
    u_int y2;
};

class Sprite : public  Graphics {
    private:
        std::string json_filename_;
        std::unordered_map<std::string,std::vector<std::unique_ptr<Animation>>> animation_list_;
        std::string current_animation_;

        int LoadJSON();
    public:
        uint width;
        uint height;

        Sprite();
        ~Sprite();

        int Load(std::string const &file_name);
        void Draw(u_int x, u_int y) override;
};

#endif