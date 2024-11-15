#include "scriptcore.h"

#include <luabridge3/LuaBridge/LuaBridge.h>
#include "game/game.h"
#include "game/gameobject.h"

#include "ui/button.h"

static char const *events[] = {"onClick", "onTick"};

namespace Brutal
{

void ScriptCore::Setup() {
    if (lua_state_ != NULL) {
        lua_close(lua_state_);
        lua_state_ = NULL;
    }

    lua_state_ = luaL_newstate();

    //TODO: Do we need the standard libs?
    luaL_openlibs(lua_state_);

    Game& game = Game::Get();
    // Collect all entity with a script component.
    auto script_view = game.level->registry_.view<ScriptComponent>();

    for (auto entity : script_view) {
        GameObject gameobject = {entity, game.level};
        auto& script_component = gameobject.GetComponent<ScriptComponent>();
        auto& uuid = gameobject.GetComponent<IDComponent>();

    //TODO: Check if a compiled version exists
    // If not preprocess it and load it

    }


    // Now bind all API's
}

void ScriptCore::Cleanup() {
    if (lua_state_ != NULL) {
        lua_close(lua_state_);
    }
}

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
    
    GameObject gameobject = game.level->GetGameObjectByUUID(event.uuid);

    if (gameobject) {
        if (event.event == EVENT_ONCLICK) {
            FormatFunction(lua_function, event.uuid, event.event);
            luabridge::LuaRef on_click = luabridge::getGlobal(lua_state_, lua_function);
            luabridge::LuaResult result = on_click();
        }
    }

}

// We rename functions from 'onTick' to '_<uuid>_onTick' to namespace it globaly
void ScriptCore::FormatFunction(char* name, int UUID, int event) 
{
    sprintf(name, "_%d_%s",UUID, events[event]);
}
}