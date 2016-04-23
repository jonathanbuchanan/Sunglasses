// Copyright 2016 Jonathan Buchanan.
// This file is part of Sunglasses, which is licensed under the MIT License.
// See LICENSE.md for details.
#ifndef SUNLUAPRIMITIVES_H
#define SUNLUAPRIMITIVES_H

#include <lua.hpp>

namespace SunScripting {
    /// Gets an element from the Lua stack
    /**
     * @param l The Lua state
     * @param index The index of the item on the stack
     */
    template<typename T>
    T getFromStack(lua_State *l, int index);

    template<> int getFromStack(lua_State *l, int index);
    template<> double getFromStack(lua_State *l, int index);
    template<> float getFromStack(lua_State *l, int index);
    template<> bool getFromStack(lua_State *l, int index);
    template<> const char * getFromStack(lua_State *l, int index);


    /// Pushes an element to the Lua stack
    /**
     * @param l The Lua state
     * @param value The value of the item to pushToStack on the stack
     */
    template<typename T>
    void pushToStack(lua_State *l, T value);

    template<> void pushToStack(lua_State *l, int value);
    template<> void pushToStack(lua_State *l, double value);
    template<> void pushToStack(lua_State *l, float value);
    template<> void pushToStack(lua_State *l, bool value);
    template<> void pushToStack(lua_State *l, const char *value);
}

#endif
