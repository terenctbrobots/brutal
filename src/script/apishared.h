#include <string>
#include "game/gameobject.h"

namespace Brutal
{
class APIShared
{
   public:
    static void SetText(std::string const& text, entt::entity entity);
};
}  // namespace brutal