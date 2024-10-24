#include "animation.h"

Animation::Animation(float start_y, float width, float height,u_int frames, u_int rate,Vector2 offset) 
{
    this->frame_rate = rate;
    this->frames = frames;
    this->offset = offset;
    this->width = width;
    this->height = height;
    
    for (int x_count=0; x_count < frames; x_count++) 
    {
        float x = x_count*width;
        frame_list.push_back(std::unique_ptr<Rectangle>(new Rectangle{x,start_y,width,height}));
    }
}

void Animation::FlipX()
{
    for (auto& rect_ptr: frame_list)
    {
        rect_ptr->width *= -1;
    }
}

void Animation::FlipY()
{
    for (auto& rect_ptr: frame_list)
    {
        rect_ptr->height *= -1;
    }
}

void Animation::Reset()
{
    for (auto& rect_ptr: frame_list) 
    {
        rect_ptr->width = width;
        rect_ptr->height = height;
    }
}