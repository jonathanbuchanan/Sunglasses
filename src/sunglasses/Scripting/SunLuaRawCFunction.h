// Copyright 2016 Jonathan Buchanan.
// This file is part of Sunglasses, which is licensed under the MIT License.
// See LICENSE.md for details.
#ifndef SUNLUARAWCFUNCTION_H
#define SUNLUARAWCFUNCTION_H

#include <sunglasses/Scripting/SunLuaCFunction.h>

namespace _SunPrivateScripting {

    class SunLuaRawCFunction : public _SunLuaCFunction_Base {
    public:
        SunLuaRawCFunction(lua_State *state, std::string _name, std::function<void(lua_State *)> _function, bool tableMember) {
            name = _name;
            function = _function;
            if (tableMember)
                registerAsTableMember(state);
        }

        void registerAsTableMember(lua_State *state) {
            lua_pushstring(state, name.c_str()); // Push name of function
            lua_pushlightuserdata(state, (void *)static_cast<_SunPrivateScripting::_SunLuaCFunction_Base *>(this)); // Upvalue pointer to this
            lua_pushcclosure(state, &callFunction, 1); // Push C Closure
            lua_settable(state, -3);
        }

        void run(lua_State *state) {
            function(state);
        }

    private:
        std::string name;
        std::function<void(lua_State *)> function;
    };
}

#endif
