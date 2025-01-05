#include "editor/window/window.h"

namespace Editor
{
class GameObjectWindow : public Window
{
  private:
    Rectangle m_GameObjectListBounds;
    std::string m_GameObjectListString;
    int m_GameObjectScrollIndex = 0;
    int m_GameObjectActive = -1;
    int m_LastGameObjectActive = -1;

    Rectangle m_AddBounds;
    Rectangle m_RemoveBounds;
    Rectangle m_MoveUpBounds;
    Rectangle m_MoveDownBounds;
    
  public:
    int m_GameObjectSelect=-1;

    void Resize() override final;
    void Draw() override final;
    void Interact(Vector2 click) override final;
};
} // namespace Editor