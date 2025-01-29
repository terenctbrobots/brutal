#pragma once

#include <string>

#include "script/apigameobject.h"
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

  public:
    static void Bind(lua_State *L);

    // Global API
    static APIGameObject &FindGameObjectByName(std::string const &name);

    static void SetText(std::string const &text);
    static void SetPosition(float x, float y);
};
} // namespace Brutal
