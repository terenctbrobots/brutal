#ifndef ANIMATION_H
#define ANIMATION_H

#include <vector>
#include <memory>
#include <sys/types.h>
#include "raylib.h"
#include "graphics.h"

class Animation 
{
    public:
        Animation(float start_y, float width, float height,u_int frames,u_int rate);

        std::vector<std::unique_ptr<Rectangle>> frame_list;
        u_int frame_rate;
        u_int frames;
};


#endif