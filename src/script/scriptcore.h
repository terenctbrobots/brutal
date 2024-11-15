#pragma once

#include <cstdint>
#include <iostream>
#include <memory>
#include <string_view>
#include <deque>

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
    int UUID;
    int event;
};

class ScriptCore {
    private:
        //TODO: Is a vector a better fit?
        std::deque<ScriptEvent> event_queue_;
        lua_State* luaState_;
   public:
    void Setup();
    void Process();
    void Cleanup();

    void AddEvent(ScriptEvent const& event);
    void ActivateEvent(ScriptEvent const& event);
};
    
}
