#include "script/apigameobject.h"
#include "script/apishared.h"
#include <luabridge3/LuaBridge/LuaBridge.h>

#include <cstdint>
#include <string>

#include "game/game.h"
#include "ui/text.h"

namespace Brutal
{
void APIGameObject::Bind(lua_State* L)
{
    luabridge::getGlobalNamespace(L)
        .beginClass<APIGameObject>("APIGameObject")
        .addFunction("setText", &APIGameObject::SetText)
        .addFunction("setPosition", &APIGameObject::SetPosition)
        .endClass();
}

void APIGameObject::SetText(std::string const& text)
{
    APIShared::SetText(text, m_Entity);
}

void APIGameObject::SetPosition(float x, float y)
{
    APIShared::SetPosition(x,y,m_Entity);
}
}  // namespace Brutal