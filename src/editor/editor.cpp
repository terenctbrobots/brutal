#include "editor/editor.h"

namespace Editor
{
Editor::Editor(float width, float height)
{
    m_EditorWindow = std::make_unique<EditorWindow>();
    m_EditorWindow->m_Bounds = {0, 0, width, height};
}

Editor::~Editor() {}

void Editor::Draw()
{
    if (m_EditorWindow)
    {
        m_EditorWindow->Draw();
    }
}
} // namespace Editor