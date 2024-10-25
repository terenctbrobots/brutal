#include <fstream>
#include <vector>
#include <memory>
#include <iostream>
#include "nlohmann/json.hpp"
using json = nlohmann::json;

#include "helper.h"
#include "sprite.h"

Sprite::Sprite() 
{
    current_animation_ = nullptr;
    current_frame_ = 0;
    next_draw_time_ = 0;
    frame_offset_ = {0,0};
}

Sprite::~Sprite() 
{
    if (texture_.id > 0) 
    {
        UnloadTexture(texture_);
    }
}
/*
* Private
*/

/**
 * @brief load json metdata data for sprite, populate and create
 * 
 * @return int - enumerated success(0) or error codes (i.e.Graphics::ERROR_)
 */
int Sprite::LoadJSON() 
{
    std::ifstream json_file(json_filename_);

    if (!json_file.good()) 
    {
        return Graphics::ERROR_JSON_LOAD;
    }

    json json_data = json::parse(json_file,nullptr,false);

    if (json_data == nullptr) 
    {
        return Graphics::ERROR_JSON_LOAD;
    }

    if (json_data["width"] != nullptr) 
    {
        width = json_data["width"];
    } else {
        width = 32;
    }

    if (json_data["height"] != nullptr) 
    {
        height = json_data["height"];
    } else {
        height = 32;
    }

    animation_list_.clear();
    
    json animation_list_json = json_data["animation"];

    u_int y = 0;
        
    for (auto &animation_json : animation_list_json.items())
    {
        json frame_data = animation_json.value();

        if (frame_data["frames"] == nullptr) 
        {
            return Graphics::ERROR_JSON;
        }

        if (frame_data["frameRate"] == nullptr) 
        {
            return Graphics::ERROR_JSON;
        }

        Vector2 offset = {0,0};

        if (frame_data["offsetX"] != nullptr)
        {
            offset.x = width * (double)frame_data["offsetX"];
        }

        if (frame_data["offsetY"] != nullptr) 
        {
            offset.y = height * (double)frame_data["offsetY"];
        }

        animation_list_[animation_json.key()] = std::make_shared<Animation>(y,width,height,frame_data["frames"],frame_data["frameRate"],offset);

        y+=height;
    }

    if (json_data["defaultAnimation"] != nullptr) 
    {
        SetAnimation(json_data["defaultAnimation"]);
    }

    return Graphics::OK;
}


/*
* Public
*/

/**
 * @brief Loads a sprite sheet in to memory and reads a corresponding json meta data file(i.e. archer.jpg=>archer.json)
 * 
 * @param file_name 
 * @return int 
 */
int Sprite::Load(std::string const& file_name) 
{
    texture_ = LoadTexture(file_name.c_str());

    if (texture_.id == 0) 
    {
        return Graphics::ERROR_TEXTURE_LOAD;   
    }

    json_filename_ = GetJSONFilename(file_name);

    if (json_filename_.length() == 0) {
        return Graphics::ERROR_JSON_FILENAME;
    }

    int return_value = LoadJSON(); 

    if ( return_value != Graphics::OK) {
        return return_value;
    }


    return Graphics::OK;
}

void Sprite::Draw(Vector2 const& position, uint tile_id) 
{
    if (current_animation_ == nullptr) 
    {
        return;
    }

    uint64_t current_time = TimeMillisec();

    if (next_draw_time_ == 0 || current_time >= next_draw_time_) 
    {
        next_draw_time_ = current_time + current_animation_->frame_rate;
        current_frame_++;
        if (current_frame_ == current_animation_->frames) 
        {
            current_frame_ = 0;
        }
    }

    Vector2 offset_position = position - current_animation_->offset;
    DrawTextureRec(texture_, *current_animation_->frame_list[current_frame_],offset_position, WHITE);
}

int Sprite::SetAnimation(std::string const &animation) 
{
    if (!animation_list_[animation]) 
    {
        return Sprite::ERROR_ANIMATION;
    }

    if (current_animation_ != nullptr) 
    {
        current_animation_->Reset();
    }
    
    current_frame_ = 0;
    current_animation_ = animation_list_[animation];

    return Graphics::OK;
}

void Sprite::FlipX()
{
    if (current_animation_ != nullptr) 
    {
        current_animation_->FlipX();
    }
}

void Sprite::FlipY()
{
    if (current_animation_ != nullptr)
    {
        current_animation_->FlipY();
    }
}