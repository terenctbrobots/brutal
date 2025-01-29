#include "editor/editor.h"

namespace Editor
{
Editor::Editor(float width, float height)
{
    m_EditorWindow = std::make_unique<EditorWindow>();
    m_GameObjectWindow = std::make_unique<GameObjectWindow>();

    Resize(width, height);
}

Editor::~Editor() {}

void Editor::Draw()
{
    if (m_EditorWindow)
    {
        m_EditorWindow->Draw();
    }

    if (m_GameObjectWindow && m_GameObjectWindow->m_Enabled)
    {
        m_GameObjectWindow->Draw();
    }
}

void Editor::Resize(float width, float height)
{
    m_EditorWindow->m_Bounds = {0, 0, width, height};

    // GameObject Window is snap right, 30% of width, 50% of height
    m_GameObjectWindow->m_Bounds = {0, 0, width * 0.2f, height * 0.5f};
    m_GameObjectWindow->Resize();
}
} // namespace Editor