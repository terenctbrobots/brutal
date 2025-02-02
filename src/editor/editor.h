#pragma once

#include <memory>
#include <vector>

namespace Editor 
{
  class Window;
  class EditorWindow;
  class GameObjectWindow;
  class LayerWindow;
  class InspectorWindow;
}

namespace Editor
{


class Editor
{
  private:
    std::shared_ptr<EditorWindow> m_EditorWindow;
    std::shared_ptr<GameObjectWindow> m_GameObjectWindow;
    std::shared_ptr<LayerWindow> m_LayerWindow;
    std::shared_ptr<InspectorWindow> m_InspectorWindow;

    std::vector<std::shared_ptr<Window>> m_DrawList;

  public:
    Editor() = default;
    Editor(float width, float height);
    ~Editor();

    void Resize(float width, float height);
    void Draw();
};
} // namespace Editor
