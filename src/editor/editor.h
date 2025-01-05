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
    std::unique_ptr<GameObjectWindow> m_GameObjectWindow;

  public:
    Editor() = default;
    Editor(float width, float height);
    ~Editor();

    void Resize(float width, float height);
    void Draw();
};
} // namespace Editor
