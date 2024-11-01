#include "gameobject.h"
#include "graphics/sprite.h"
#include "helper.h"

GameObject::GameObject(std::string const& name)
{
    uid_ = GetNextUid();
}

GameObject::~GameObject()
{

}


int GameObject::LoadSprite(std::string const& file_name)
{
    graphics_ = std::make_shared<Sprite>();
    return graphics_->Load(file_name);
}