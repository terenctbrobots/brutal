#include "apigameobject.h"

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
    Game& game = Game::Get();

    GameObject gameobject = {m_Entity, game.level};

    if (gameobject)
    {
        if (gameobject.HasComponent<TextComponent>())
        {
            auto& textComponent = gameobject.GetComponent<TextComponent>();
            textComponent.m_TextField = text;
#ifdef DEBUG
    spdlog::info("APIGameObject: setText with {}",text);
#endif
        }
    }
}
}  // namespace Brutal