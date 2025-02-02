#include "editor/window/layerwindow.h"

#include "spdlog/spdlog.h"

namespace Editor
{
void LayerWindow::Draw()
{
    Window::Draw();

    int currentActive;

    GuiListView(m_LayerListBounds, m_LayerListString.c_str(), &m_LayerScrollIndex, &m_LayerActive);

    if (m_LastLayerActive != m_LayerActive)
    {
        m_LastLayerActive = m_LayerActive;
        spdlog::info("Layer active {}", m_LayerActive);
    }


}

void LayerWindow::Resize()
{
    m_LayerListBounds = Rectangle{m_Bounds.x, m_Bounds.y, m_Bounds.width, m_Bounds.height};

    m_LayerListString = "Layer1;Layer2;Layer3;Layer4;Layer5;Layer6;Layer7;Layer8;Layer9;Layer10;"
                             "Layer11;Layer12;Layer13;Layer14;Layer15";
}

void LayerWindow::Interact(Vector2 click) {}
} // namespace Editor