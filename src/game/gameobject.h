#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H

#include <cstdint>
#include <memory>
#include <string>

#include "raylib.h"
#include "render.h"

class GameObject {
   protected:
    std::shared_ptr<Render> render_;
    u_int64_t uid_;

   public:
    std::string name;
    Rectangle position;

    GameObject(std::string const& name);
    ~GameObject();

    u_int64_t GetUid();
    int Add(std::shared_ptr<Render> graphic);

    int LoadSprite(std::string const& file_name);
    void Draw();
};

#endif