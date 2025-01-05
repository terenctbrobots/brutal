#include "editor/window/window.h"

namespace Editor
{
void Window::Draw() { DrawRectangleLinesEx(m_Bounds, 2.0f, RED); }
void Window::Resize() {};

} // namespace Editor