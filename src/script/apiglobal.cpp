#include "apiglobal.h"

#include <luabridge3/LuaBridge/LuaBridge.h>

#include <cstdint>

#include "game/game.h"

namespace Brutal
{
APIGameObject APIGlobal::api_ = APIGameObject();

void APIGlobal::Bind(lua_State* L)
{
    api_.Bind(L);

    luabridge::getGlobalNamespace(L).addFunction("findGameObjectByName", &APIGlobal::FindGameObjectByName);
}

APIGameObject& APIGlobal::FindGameObjectByName(std::string const& name)
{
    Game& game = Game::Get();

    api_.m_Entity = game.level->FindGameObjectByName(name);

#ifdef DEBUG
    spdlog::info("APIGlobal: FindingObjectByName {} Entity is {}",name,(u_int32_t)api_.m_Entity);
#endif

    return api_;
}
}  // namespace Brutal