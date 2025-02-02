#include "editor/window/inspectorwindow.h"

#include "editor/component/component.h"

#include "game/gameobject.h"
#include "graphics/bitmap.h"
#include "graphics/sprite.h"
#include "ui/button.h"
#include "ui/text.h"

#include "spdlog/spdlog.h"

namespace Editor
{
void InspectorWindow::Draw()
{
    Window::Draw();
}

void InspectorWindow::Resize()
{
}

void InspectorWindow::SetGameObject( Brutal::GameObject& gameObject) 
{

    if (gameObject.HasComponent<Brutal::BitmapComponent>())
    {
    }

    if (gameObject.HasComponent<Brutal::SpriteComponent>())
    {
    }

    if (gameObject.HasComponent<Brutal::ButtonComponent>())
    {
    }

    if (gameObject.HasComponent<Brutal::TextComponent>())
    {
    }
}

void InspectorWindow::Interact(Vector2 click) {}
} // namespace Editor