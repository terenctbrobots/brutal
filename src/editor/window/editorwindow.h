#include "editor/window/window.h"

namespace Editor
{
class EditorWindow : public Window
{
   public:
    void Draw() override final;
    void Interact(Vector2 click) override final;
};
}  // namespace Editor