#include "game/game.h"
#include "ui/text.h"
#include "script/apishared.h"

namespace Brutal
{
void APIShared::SetText(std::string const& text, entt::entity const& entity)
{
    GameObject gameobject = {entity, Game::GetLevel()};

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

void APIShared::SetPosition(float x, float y, entt::entity const& entity) 
{
    GameObject gameObject = {entity,Game::GetLevel()};

    if (gameObject) 
    {
        auto& rectangleComponent = gameObject.GetComponent<Rectangle>();
        rectangleComponent.x = x;
        rectangleComponent.y = y;
    }
}
}  // namespace Brutal