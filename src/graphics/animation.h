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
        //TODO: Pass a structure istead?
        Animation(float start_y, float width, float height,u_int frames,u_int rate,Vector2 offset);

        std::vector<std::unique_ptr<Rectangle>> frame_list;
        u_int frame_rate;
        u_int frames;
        Vector2 offset;
};


#endif