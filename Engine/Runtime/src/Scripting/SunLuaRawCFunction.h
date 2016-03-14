// Copyright 2016 Jonathan Buchanan.
// This file is part of Sunglasses, which is licensed under the MIT License.
// See LICENSE.md for details.
#ifndef SUNLUARAWCFUNCTION_H
#define SUNLUARAWCFUNCTION_H

#include "SunLuaCFunction.h"

namespace _SunPrivateScripting {

    class SunLuaRawCFunction : public _SunLuaCFunction_Base {
    public:
        SunLuaRawCFunction(SunLuaState *state, std::string _name, std::function<void(lua_State *)> _function, bool tableMember) {
            name = _name;
            function = _function;
            if (tableMember)
                registerAsTableMember(state);
        }

        void registerAsTableMember(SunLuaState *state) {
            state->pushString(name.c_str()); // Push name of function
            state->pushLightUserdata((void *)static_cast<_SunPrivateScripting::_SunLuaCFunction_Base *>(this)); // Upvalue pointer to this
            state->pushCClosure(&callFunction, 1); // Push C Closure
            state->setTable(-3);
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
