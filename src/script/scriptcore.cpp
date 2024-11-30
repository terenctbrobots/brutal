#include "scriptcore.h"

#include <luabridge3/LuaBridge/LuaBridge.h>
#include "game/game.h"
#include "game/gameobject.h"
#include <fstream>
#include <iostream>
#include <string>

#include "ui/button.h"

#include "apiglobal.h"

static char const *events[] = {"onClick", "onTick"};
constexpr int event_size() { return sizeof(events) / sizeof(events[0]); }

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

        std::optional<std::string> script_buffer = PreProcessScript(script_component.m_Filename, uuid.m_ID);

        if (script_buffer.has_value()) {
            luaL_loadstring(L_, script_buffer->c_str());
        } else {
            spdlog::error("ScriptCore : could not load or process {} file",script_component.m_Filename);
            abort();
        }
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
    Game& game = Game::Get();
    
    GameObject gameobject = game.level->GetGameObjectByUUID(event.uuid);

    if (gameobject) {
        if (event.event == EVENT_ONCLICK) {
            //FormatFunction(lua_function, event.uuid, event.event);
            luabridge::LuaRef on_click = luabridge::getGlobal(L_, FormatFunction(event).c_str());
            luabridge::LuaResult result = on_click();
        }
    }

}

// We rename functions from 'onTick' to '_<uuid>_onTick' to namespace it globaly
std::string ScriptCore::FormatFunction(ScriptEvent const& event) 
{
    char function_name[80];
    sprintf(function_name, "_%lu_%s",event.uuid, events[event.event]);

    return function_name;
}

std::optional<std::string> ScriptCore::PreProcessScript(std::string const& filename, u_int64_t uuid) {
    std::ifstream file(filename);

    if (!file.good()) {
        return std::nullopt;
    }

    std::string file_contents((std::istreambuf_iterator<char>(file)), std::istreambuf_iterator<char>());

    for (int i=0; i < event_size(); i++) {
        std::string from = events[i];
        from += "(";
        std::string to = FormatFunction({i,uuid}) + "(";
        std::size_t pos = file_contents.find(from);

        if (pos != std::string::npos) {
            file_contents.replace(pos,from.length(), to);
        }
    }
    
    return file_contents;
}

ScriptComponent ScriptCore::Deserialize(json const& json_data) {
    ScriptComponent script;

    script.m_Filename = json_data["fileName"];
    script.m_OnTick = json_data["onTick"];

    return script;
}
}