#pragma once

#include <cstdint>
#include <iostream>
#include <memory>
#include <string_view>
#include <deque>
#include "game/component.h"
#include "common.h"
#include <optional>

extern "C" {
#include "lauxlib.h"
#include "lua.h"
#include "lualib.h"
}

namespace Brutal {
enum EventType {
    EVENT_ONCLICK = 0,
    EVENT_ONTICK = 1,
};

struct ScriptEvent {
    int event;
    u_int64_t uuid;
};

class ScriptCore {
    private:
        //TODO: Is a vector a better fit?
        std::deque<ScriptEvent> event_queue_;
        lua_State* L_ = NULL;

   public:
    void Setup();
    void Process();
    void Cleanup();

    std::string FormatFunction(ScriptEvent const& event);
    std::optional<std::string> PreProcessScript(std::string const& filename, u_int64_t uuid);
    void AddEvent(ScriptEvent const& event);
    void ActivateEvent(ScriptEvent const& event);
    static ScriptComponent Deserialize(json const& json_data);
};
    
}
