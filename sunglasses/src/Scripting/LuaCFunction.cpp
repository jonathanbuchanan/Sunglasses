// Copyright 2016 Jonathan Buchanan.
// This file is part of glasses, which is licensed under the MIT License.
// See LICENSE.md for details.
#include <sunglasses/Scripting/LuaCFunction.h>

namespace sunglasses {

namespace _PrivateScripting {
    int callFunction(lua_State *state) {
        _LuaCFunction_Base *base = (_LuaCFunction_Base *)lua_touserdata(state, lua_upvalueindex(1));
        base->run(state);
        return 1;
    }
}

} // namespace
