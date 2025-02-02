#include "editor/editor.h"

#include "editor/window/editorwindow.h"
#include "editor/window/gameobjectwindow.h"
#include "editor/window/layerwindow.h"
#include "editor/window/inspectorwindow.h"

namespace Editor
{
Editor::Editor(float width, float height)
{
    m_EditorWindow = std::make_shared<EditorWindow>();
    m_DrawList.push_back(m_EditorWindow);
    m_GameObjectWindow = std::make_shared<GameObjectWindow>();
    m_DrawList.push_back(m_GameObjectWindow);
    m_LayerWindow = std::make_shared<LayerWindow>();
    m_DrawList.push_back(m_LayerWindow);
    m_InspectorWindow = std::make_shared<InspectorWindow>();
    m_DrawList.push_back(m_InspectorWindow);

    Resize(width, height);
}

Editor::~Editor() {}

void Editor::Draw()
{
    for (auto& window : m_DrawList)
    {
        if (window->m_Enabled)
        {
            window->Draw();
        }
    }
}

void Editor::Resize(float width, float height)
{
    m_EditorWindow->m_Bounds = {0, 0, width, height};

    // GameObject Window is snap left, 30% of width, 50% of height
    m_GameObjectWindow->m_Bounds = {0, 0, width * 0.2f, height * 0.5f};
    m_GameObjectWindow->Resize();

    // Layer list, snap left 30% of width and remaining height
    m_LayerWindow->m_Bounds = {0,height * 0.5f,m_GameObjectWindow->m_Bounds.width,height * 0.5f};
    m_LayerWindow->Resize();

    // Inspector window, snap right 30% of widht and full height
    m_InspectorWindow->m_Bounds = {width - width * 0.3f, 0, width * 0.3f, height};
    m_InspectorWindow->Resize();
}
} // namespace Editor