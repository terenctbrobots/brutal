#include "scriptcore.h"

#include <luabridge3/LuaBridge/LuaBridge.h>

#include <fstream>
#include <iostream>
#include <string>

#include "script/apiglobal.h"
#include "game/game.h"
#include "game/gameobject.h"
#include "ui/button.h"

static char const* events[] = {"onClick", "onTick"};
constexpr int event_size() { return sizeof(events) / sizeof(events[0]); }

namespace Brutal
{

ScriptCore::~ScriptCore() 
{
    if (L_ != NULL)
    {
        lua_close(L_);
    }
}

void ScriptCore::Setup()
{
    if (L_ != NULL)
    {
        lua_close(L_);
        L_ = NULL;
    }

    L_ = luaL_newstate();

    // TODO: Do we need the standard libs?
    luaL_openlibs(L_);

    // Collect all entity with a script component.
    auto scriptView = Game::GetLevel()->registry_.view<ScriptComponent>();

    for (auto entity : scriptView)
    {
        GameObject gameobject = {entity, Game::GetLevel()};
        auto& scriptComponent = gameobject.GetComponent<ScriptComponent>();
        auto& uuid = gameobject.GetComponent<IDComponent>();

        std::optional<std::string> scriptBuffer = PreProcessScript(scriptComponent.m_Filename, uuid.m_ID);

        if (scriptBuffer.has_value())
        {
            if (luaL_dostring(L_, scriptBuffer->c_str()) != LUA_OK)
            {
                spdlog::error("ScriptCore: Could parse {}, Error:{}", scriptComponent.m_Filename, lua_tostring(L_, -1));
                abort();
            }
#ifdef DEBUG
            spdlog::info("ScriptCore: Loaded script {}", scriptComponent.m_Filename);
#endif
        }
        else
        {
            spdlog::error("ScriptCore : could not load or process {} file", scriptComponent.m_Filename);
            abort();
        }
    }

    // Now bind all API's
    APIGlobal::Bind(L_);
}

void ScriptCore::Process()
{
    while (!event_queue_.empty())
    {
        ActivateEvent(event_queue_.front());
#ifdef DEBUG
        const ScriptEvent& event = event_queue_.front();
        spdlog::info("Processing event {} with uuid {}", event.m_Event, event.m_UUID);
#endif
        event_queue_.pop_front();
    }
}

void ScriptCore::AddEvent(ScriptEvent const& event) { event_queue_.push_back(event); }

void ScriptCore::ActivateEvent(ScriptEvent const& event)
{
    GameObject gameobject = Game::GetLevel()->GetGameObjectByUUID(event.m_UUID);

    m_CurrentEntity = gameobject;
    
    if (gameobject)
    {
        switch (event.m_Event)
        {
            case EVENT_ONCLICK:
            {
                luabridge::LuaRef onClick = luabridge::getGlobal(L_, FormatFunction(event).c_str());
                luabridge::LuaResult result = onClick();
#ifdef DEBUG
                spdlog::info("ScriptCore: Called OnClick with function name {}", FormatFunction(event));
#endif
                break;
            }
            case EVENT_ONTICK:
            {
                luabridge::LuaRef onTick = luabridge::getGlobal(L_, FormatFunction(event).c_str());
                luabridge::LuaResult result = onTick(GetFrameTime());
#ifdef DEBUG
                // spdlog::info("ScriptCore: Called OnTick with function name {} and frametime {}", FormatFunction(event),
                //              GetFrameTime());
#endif
                break;
            }
        }
    }
}

// We rename functions from 'onTick' to '_<uuid>_onTick' to namespace it globaly
std::string ScriptCore::FormatFunction(ScriptEvent const& event)
{
    char functionName[80];
    sprintf(functionName, "_%lu_%s", event.m_UUID, events[event.m_Event]);

    return functionName;
}

std::optional<std::string> ScriptCore::PreProcessScript(std::string const& filename, u_int64_t uuid)
{
#ifdef DEBUG
    spdlog::info("ScriptCore: Preprocessing script {}", filename);
#endif
    std::ifstream file(filename);

    if (!file.good())
    {
        spdlog::error("ScriptCore: Could not read script {}", filename);
        return std::nullopt;
    }

    std::string file_contents((std::istreambuf_iterator<char>(file)), std::istreambuf_iterator<char>());

    for (int i = 0; i < event_size(); i++)
    {
        std::string from = events[i];
        from += "(";
        std::string to = FormatFunction({i, uuid}) + "(";
        std::size_t pos = file_contents.find(from);

        if (pos != std::string::npos)
        {
            file_contents.replace(pos, from.length(), to);
        }
    }
#ifdef DEBUG
    spdlog::info("ScriptCore: Preprocessing complete for {}", filename);
#endif

    return file_contents;
}

ScriptComponent ScriptCore::Deserialize(json const& json_data)
{
    ScriptComponent script;

    script.m_Filename = json_data["fileName"];
    if (json_data.contains("onTick"))
    {
        script.m_OnTick = json_data["onTick"];
    }
    else
    {
        script.m_OnTick = false;
    }

    return script;
}
}  // namespace Brutal