#pragma once

#include <string>

#include "apigameobject.h"
extern "C"
{
#include "lauxlib.h"
#include "lua.h"
#include "lualib.h"
}

namespace Brutal
{
class APIGlobal
{
   private:
    static APIGameObject api_;
    friend APIGlobal;

   public:
    static void Bind(lua_State* L);

    //Global API
    static APIGameObject& FindGameObjectByName(std::string const& name);
};
}  // namespace Brutal
