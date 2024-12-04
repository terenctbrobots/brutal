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
        .endClass();
}

void APIGameObject::SetText(std::string const& text)
{
    APIShared::SetText(text, m_Entity);
}
}  // namespace Brutal