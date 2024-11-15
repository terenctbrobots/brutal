#include "scriptcore.h"

#include <luabridge3/LuaBridge/LuaBridge.h>

void ScriptCore::Setup() {}

void ScriptCore::Cleanup() {}

void ScriptCore::Process() {}

void ScriptCore::AddEvent(ScriptEvent const& event) {
    event_queue_.push_back(event);
}