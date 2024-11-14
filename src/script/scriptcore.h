#ifndef SCRIPTCORE_H_
#define SCRIPTCORE_H_

#include <cstdint>
#include <iostream>
#include <memory>
#include <string_view>

extern "C" {
#include "lauxlib.h"
#include "lua.h"
#include "lualib.h"
}

class ScriptCore {
   public:
    void Setup();
    void Cleanup();
};

#endif