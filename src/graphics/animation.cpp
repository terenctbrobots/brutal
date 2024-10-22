#include "animation.h"

Animation::Animation(float start_y, float width, float height,u_int frames, u_int rate) 
{
    this->frame_rate = rate;
    this->frames = frames;
    
    for (int x_count=0; x_count < frames; x_count++) 
    {
        float x = x_count*width;
        frame_list.push_back(std::unique_ptr<Rectangle>(new Rectangle{x,start_y,width,height}));
    }
}