#include "editor/component/component.h"

namespace Editor
{
void Component::Draw()
{
    DrawRectangleLinesEx(m_Bounds, 2.0f, BLUE);

    GuiTextBox({m_Bounds.x + 2, m_Bounds.y + 2,m_Bounds.width - 2, 10},m_Name,10,false);
}
void Component::Resize() {};

} // namespace Editor