#include "game/game.h"
#include "ui/text.h"
#include "script/apishared.h"

namespace Brutal
{
void APIShared::SetText(std::string const& text, entt::entity entity)
{
    Game& game = Game::Get();
    GameObject gameobject = {entity, game.level};

    if (gameobject)
    {
        if (gameobject.HasComponent<TextComponent>())
        {
            auto& textComponent = gameobject.GetComponent<TextComponent>();
            textComponent.m_TextField = text;
#ifdef DEBUG
            spdlog::info("APIShared: setText with {}", text);
#endif
        }
    }
}
}  // namespace Brutal