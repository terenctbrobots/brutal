#include <string>
#include "game/gameobject.h"

namespace Brutal
{
class APIShared
{
   public:
    static void SetText(std::string const& text, entt::entity const& entity);
    static void SetPosition(float x,float y, entt::entity const& entity);
};
}  // namespace brutal