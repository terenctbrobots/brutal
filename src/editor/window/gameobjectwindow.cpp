#include "editor/window/gameobjectwindow.h"

#include "spdlog/spdlog.h"

namespace Editor
{
void GameObjectWindow::Draw()
{
   Window::Draw();

   int currentActive;

   GuiListView(m_GameObjectListBounds,m_GameObjectListString.c_str(),&m_GameObjectScrollIndex,&m_GameObjectActive);

   if (m_LastGameObjectActive != m_GameObjectActive) 
   {
      m_LastGameObjectActive = m_GameObjectActive;
      spdlog::info("GameObject active {}",m_GameObjectActive);
   }

   if (GuiButton(m_AddBounds,"+")) 
   {
      spdlog::info("Add Gameobject");
   }

   if (GuiButton(m_RemoveBounds,"-"))
   {
      spdlog::info("Remove Gameobject");
   }

   if (GuiButton(m_MoveUpBounds,GuiIconText(ICON_ARROW_UP,"")))
   {
      spdlog::info("Move Up");
   }

   if (GuiButton(m_MoveDownBounds,GuiIconText(ICON_ARROW_DOWN,"")))
   {
      spdlog::info("Move Down");
   }
}

void GameObjectWindow::Resize() 
{
   m_GameObjectListBounds = Rectangle 
   {
      m_Bounds.x,m_Bounds.y,m_Bounds.width,m_Bounds.height * 0.9f
   };

   m_GameObjectListString = "Object1;Object2;Object3;Object4;Object5;Object6;Object7;Object8;Object9;Object10;Object11;Object12;Object13;Object14;Object15";

   float buttonWidth = m_Bounds.width/4;
   float buttonHeight = m_Bounds.height * 0.1f;
   float buttonY = m_Bounds.y + m_Bounds.height * 0.9f;

   m_AddBounds = Rectangle
   {
      m_Bounds.x,
      buttonY,
      buttonWidth, buttonHeight
   };

   m_RemoveBounds = Rectangle
   {
      m_Bounds.x + buttonWidth,
      buttonY,
      buttonWidth, buttonHeight
   };

   m_MoveUpBounds = Rectangle
   {
      m_Bounds.x + 2*buttonWidth,
      buttonY,
      buttonWidth,buttonHeight
   };

   m_MoveDownBounds = Rectangle
   {
      m_Bounds.x + 3*buttonWidth,
      buttonY,
      buttonWidth,buttonHeight
   };
}

void GameObjectWindow::Interact(Vector2 click) {}
} // namespace Editor