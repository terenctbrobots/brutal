#include "scriptcore.h"

#include <luabridge3/LuaBridge/LuaBridge.h>
#include "game/game.h"
#include "game/gameobject.h"

#include "ui/button.h"

static char const *events[] = {"onClick", "onTick"};
namespace Brutal
{

void ScriptCore::Setup() {
    luaState_ = luaL_newstate();

    //TODO: Do we need the standard libs?
    luaL_openlibs(luaState_);

    // Collect all entity with a script component.
    // Check if a compiled version exists
    // If not preprocess it and load it

    // Now bind all API's
}

void ScriptCore::Cleanup() {}

void ScriptCore::Process() {
    while (!event_queue_.empty()) {
        ActivateEvent(event_queue_.front());
        event_queue_.pop_front();
    }
}

void ScriptCore::AddEvent(ScriptEvent const& event) {
    event_queue_.push_back(event);
}

void ScriptCore::ActivateEvent(ScriptEvent const& event) {
    char lua_function[80];

    Game& game = Game::Get();
    
    GameObject gameobject = game.level->GetGameObjectByUUID(event.UUID);

    if (gameobject) {
        if (event.event == EVENT_ONCLICK) {
            sprintf(lua_function,"%d::%s",event.UUID,events[event.event]);
            luabridge::LuaRef on_click = luabridge::getGlobal(luaState_, lua_function);
            luabridge::LuaResult result = on_click();
        }
    }

}
}