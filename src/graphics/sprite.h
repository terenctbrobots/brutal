#ifndef SPRITE_H
#define SPRITE_H
#include <string>
#include "raylib.h"
#include "graphics.h"
#include "animation.h"

class Sprite : public  Graphics 
{
    private:
        std::string json_filename_;
        std::unordered_map<std::string,std::shared_ptr<Animation>> animation_list_;
        Texture2D texture_;

        std::shared_ptr<Animation> current_animation_;
        u_int current_frame_;
        u_int64_t next_draw_time_;

        Vector2 frame_offset_;

    private:
        int LoadJSON();

    public:
        enum ReturnType 
        {
            ERROR_ANIMATION = Graphics::ERROR_GRAPHIC_LAST,
            ERROR_SPRITE_LAST,
        };

        uint32_t width;
        uint32_t height;

    public:
        Sprite();
        ~Sprite();

        int Load(std::string const& file_name);
        int SetAnimation(std::string const& animation);
        void Draw(Vector2 const& position, uint32_t tile_id = 0) override;

        void FlipX();
        void FlipY();
};

#endif