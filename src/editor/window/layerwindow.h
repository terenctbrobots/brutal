#pragma once

#include "editor/window/window.h"

namespace Editor
{
class LayerWindow : public Window
{
  private:
    Rectangle m_LayerListBounds;
    std::string m_LayerListString;
    int m_LayerScrollIndex = 0;
    int m_LayerActive = -1;
    int m_LastLayerActive = -1;

  public:

    void Resize() override final;
    void Draw() override final;
    void Interact(Vector2 click) override final;
};
} // namespace Editor