// Copyright 2016 Jonathan Buchanan.
// This file is part of Sunglasses, which is licensed under the MIT License.
// See LICENSE.md for details.
#include <sunglasses/Scripting/SunLuaValue.h>

namespace _SunPrivateScripting {
    SunLuaValue::SunLuaValue(lua_State *s, bool _isFunctionReturn, int _index) {
        state = s;
        isFunctionReturn = _isFunctionReturn;
        index = _index;
    }

    void SunLuaValue::newTable() {
        if (tables.size() > 1) {
            setUpSetTable();
            lua_pushstring(state, (const char *)tables[tables.size() - 1]);
        }
        lua_newtable(state);
        if (tables.size() < 2)
            lua_setglobal(state, (const char *)tables[tables.size() - 1]);
        else
            lua_settable(state, -3);
    }

    SunLuaValue::operator int() {
        getGlobal();
        int x = lua_tointeger(state, index);
        cleanGet();
        return x;
    }

    SunLuaValue::operator double() {
        getGlobal();
        double x = lua_tonumber(state, index);
        cleanGet();
        return x;
    }

    SunLuaValue::operator bool() {
        getGlobal();
        bool x = lua_toboolean(state, index);
        cleanGet();
        return x;
    }

    SunLuaValue::operator std::string() {
        getGlobal();
        std::string x = std::string(lua_tostring(state, index));
        cleanGet();
        return x;
    }

    SunLuaValue SunLuaValue::operator[](const int &element) {
        return SunLuaValue(state, tables, _SunPrivateScripting::SunLuaPrimitive(element));
    }

    SunLuaValue SunLuaValue::operator[](const char *element) {
        return SunLuaValue(state, tables, _SunPrivateScripting::SunLuaPrimitive(element));
    }

    void SunLuaValue::operator=(const int &x) {
        if (tables.size() < 2) {
            lua_pushinteger(state, x);
            lua_setglobal(state, (const char *)tables[tables.size() - 1]);
        } else {
            setUpSetTable();
            tables[tables.size() - 1].push(state);
            lua_pushinteger(state, x);
            lua_settable(state, -3);
            cleanUpSetTable();
        }
    }

    void SunLuaValue::operator=(const double &x) {
        if (tables.size() < 2) {
            lua_pushnumber(state, x);
            lua_setglobal(state, (const char *)tables[tables.size() - 1]);
        } else {
            setUpSetTable();
            tables[tables.size() - 1].push(state);
            lua_pushnumber(state, x);
            lua_settable(state, -3);
            cleanUpSetTable();
        }
    }

    void SunLuaValue::operator=(const bool &x) {
        if (tables.size() < 2) {
            lua_pushboolean(state, x);
            lua_setglobal(state, (const char *)tables[tables.size() - 1]);
        } else {
            setUpSetTable();
            tables[tables.size() - 1].push(state);
            lua_pushboolean(state, x);
            lua_settable(state, -3);
            cleanUpSetTable();
        }
    }

    void SunLuaValue::operator=(const char *x) {
        if (tables.size() < 2) {
            lua_pushstring(state, x);
            lua_setglobal(state, (const char *)tables[tables.size() - 1]);
        } else {
            setUpSetTable();
            tables[tables.size() - 1].push(state);
            lua_pushstring(state, x);
            lua_settable(state, -3);
            cleanUpSetTable();
        }
    }

    void SunLuaValue::setNil() {
        if (tables.size() < 2) {
            lua_pushnil(state);
            lua_setglobal(state, (const char *)tables[tables.size() - 1]);
        } else {
            setUpSetTable();
            tables[tables.size() - 1].push(state);
            lua_pushnil(state);
            lua_settable(state, -3);
            cleanUpSetTable();
        }
    }

    void SunLuaValue::getGlobal() {
        if (isFunctionReturn)
            return;
        if (tables.size() < 2)
            lua_getglobal(state, (const char *)tables[tables.size() - 1]);
        else
            setUpGetTable();
    }

    void SunLuaValue::cleanGet() {
        if (tables.size() < 2)
            lua_remove(state, index);
        else
            cleanUpGetTable();
    }

    void SunLuaValue::setUpGetTable() {
        // Global Table
        lua_getglobal(state, (const char *)tables[0]);
        tables[1].push(state);
        lua_gettable(state, -2);
        for (size_t i = 1; i < tables.size() - 1; i++) {
            tables[i + 1].push(state);
            lua_gettable(state, -2);
        }
    }

    void SunLuaValue::cleanUpGetTable() {
        lua_pop(state, tables.size());
    }

    void SunLuaValue::setUpSetTable() {
        // Global Table
        lua_getglobal(state, (const char *)tables[0]);
        for (size_t i = 1; i < tables.size() - 1; i++) {
            tables[i].push(state);
            lua_gettable(state, -2);
        }
    }

    void SunLuaValue::cleanUpSetTable() {
        lua_pop(state, tables.size());
    }
}
