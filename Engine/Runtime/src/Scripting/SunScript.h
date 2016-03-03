// Copyright 2016 Jonathan Buchanan.
// This file is part of Sunglasses, which is licensed under the MIT License.
// See LICENSE.md for details.
#ifndef SUNSCRIPT_H
#define SUNSCRIPT_H

#include <lua.hpp>

#include "SunLuaValue.h"
#include "SunLuaState.h"

class SunScript {
public:
    SunScript();
    ~SunScript();

    void loadFile(std::string file);

    SunLuaValue getVariable(std::string var);
    SunLuaValue operator[](std::string var);

    void run(std::string code);
    void operator()(std::string code);

    SunLuaState * getState() { return state; }
private:
    SunLuaState *state;
};

#endif
