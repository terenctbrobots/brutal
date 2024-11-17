#include "apiglobal.h"
#include "game/game.h"
#include <cstdint>
#include <luabridge3/LuaBridge/LuaBridge.h>

namespace Brutal {
    APIGameObject APIGlobal::api_ = APIGameObject();

    void APIGlobal::Bind(lua_State* L) {        
        api_.Bind(L);

        luabridge::getGlobalNamespace(L)
            .addFunction("findGameObjectByName",&APIGlobal::findGameObjectByName);
    }

    APIGameObject& APIGlobal::findGameObjectByName(std::string const& name) {
        Game& game = Game::Get();

        api_.entity_ = game.level->FindGameObjectByName(name);

        return api_;
    }
}