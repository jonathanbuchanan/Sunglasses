// Copyright 2016 Jonathan Buchanan.
// This file is part of Sunglasses, which is licensed under the MIT License.
// See LICENSE.md for details.
#include <sunglasses/Scripting/SunLuaPrimitives.h>

namespace sunglasses {

namespace SunScripting {
    template<> int getFromStack(lua_State *l, int index) {
        return lua_tointeger(l, index);
    }

    template<> double getFromStack(lua_State *l, int index) {
        return lua_tonumber(l, index);
    }

    template<> float getFromStack(lua_State *l, int index) {
        return (float)lua_tonumber(l, index);
    }

    template<> bool getFromStack(lua_State *l, int index) {
        return lua_toboolean(l, index);
    }

    template<> const char * getFromStack(lua_State *l, int index) {
        return lua_tostring(l, index);
    }

    template<> std::string getFromStack(lua_State *l, int index) {
        return std::string(lua_tostring(l, index));
    }

    template<> void pushToStack(lua_State *l, int value) {
        lua_pushinteger(l, value);
    }

    template<> void pushToStack(lua_State *l, double value) {
        lua_pushnumber(l, value);
    }

    template<> void pushToStack(lua_State *l, float value) {
        lua_pushnumber(l, (double)value);
    }

    template<> void pushToStack(lua_State *l, bool value) {
        lua_pushboolean(l, value);
    }

    template<> void pushToStack(lua_State *l, const char *value) {
        lua_pushstring(l, value);
    }

    template<> void pushToStack(lua_State *l, std::string value) {
        lua_pushstring(l, value.c_str());
    }
}

} // namespace
