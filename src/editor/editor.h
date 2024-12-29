#include "editor/window/editorwindow.h"

#include <memory>

namespace Editor
{
class Editor
{
   private:
    std::unique_ptr<EditorWindow> m_EditorWindow;
   public:
    Editor() = default;
    Editor(float width, float height);
    ~Editor();
    void Draw();
};
}  // namespace Editor
