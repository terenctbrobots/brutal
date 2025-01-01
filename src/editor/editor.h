#include "editor/window/editorwindow.h"
#include "editor/window/gameobjectwindow.h"

#include <memory>
#include <vector>

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
} // namespace Editor
