#include "scriptcore.h"

#include <luabridge3/LuaBridge/LuaBridge.h>
#include "game/game.h"
#include "game/gameobject.h"

#include "ui/button.h"

#include "apiglobal.h"

static char const *events[] = {"onClick", "onTick"};

namespace Brutal
{

void ScriptCore::Setup() {
    if (L_ != NULL) {
        lua_close(L_);
        L_ = NULL;
    }

    L_ = luaL_newstate();

    //TODO: Do we need the standard libs?
    luaL_openlibs(L_);

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
    APIGlobal::Bind(L_);
}

void ScriptCore::Cleanup() {
    if (L_ != NULL) {
        lua_close(L_);
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
            luabridge::LuaRef on_click = luabridge::getGlobal(L_, lua_function);
            luabridge::LuaResult result = on_click();
        }
    }

}

// We rename functions from 'onTick' to '_<uuid>_onTick' to namespace it globaly
void ScriptCore::FormatFunction(char* name, int UUID, int event) 
{
    sprintf(name, "_%d_%s",UUID, events[event]);
}

ScriptComponent ScriptCore::Deserialize(json const& json_data) {
    ScriptComponent script;

    script.filename = json_data["fileName"];
    script.on_tick = json_data["onTick"];

    return script;
}
}