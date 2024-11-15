#ifndef SCRIPTCORE_H_
#define SCRIPTCORE_H_

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

struct ScriptEvent {
    int UUID;
    int event;
};

class ScriptCore {
    private:
        //TODO: Is a vector a better fit?
        std::deque<ScriptEvent> event_queue_;
   public:
    void Setup();
    void Process();
    void Cleanup();

    void AddEvent(ScriptEvent const& event);
};

#endif