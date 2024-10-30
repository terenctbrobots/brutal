#include "gameobject.h"
#include "helper.h"

GameObject::GameObject(std::string const& name)
{
    uid_ = GetNextUid();
}

GameObject::~GameObject()
{

}