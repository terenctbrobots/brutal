#include "apigameobject.h"

#include "game/game.h"
#include <cstdint>
#include <string>
#include <luabridge3/LuaBridge/LuaBridge.h>

#include "ui/text.h"

namespace Brutal 
{
    void APIGameObject::Bind(lua_State* L) {
            luabridge::getGlobalNamespace(L)
        .beginClass<APIGameObject>("APIGameObject")
        .addFunction("setText", &APIGameObject::setText)
        .endClass();

    }

    void APIGameObject::setText(std::string const& text) {
        Game& game = Game::Get();

        GameObject gameobject = {entity_,game.level};

        if (gameobject) {
            if (gameobject.HasComponent<TextComponent>()) {
                auto& text_component = gameobject.GetComponent<TextComponent>();
                text_component.text_field = text;
            }
        }
    }
}