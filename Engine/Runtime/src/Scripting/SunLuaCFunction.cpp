// Copyright 2016 Jonathan Buchanan.
// This file is part of Sunglasses, which is licensed under the MIT License.
// See LICENSE.md for details.
#include "SunLuaCFunction.h"

namespace _SunPrivateScripting {
    int callFunction(lua_State *state) {
        _SunLuaCFunction_Base *base = (_SunLuaCFunction_Base *)lua_touserdata(state, lua_upvalueindex(1));
        base->run(state);
        return 1;
    }
}
