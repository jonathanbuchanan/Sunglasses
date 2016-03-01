#include "SunLuaValue.h"
#include <iostream>

SunLuaValue::SunLuaValue(lua_State *s, const char *_var) {
    state = s;
    var = _var;
}

SunLuaValue::SunLuaValue(lua_State *s, const char *_var, bool _i, SunLuaValue *p) {
    state = s;
    var = _var;
    isTableValue = _i;
    parentTable = p;
    level = parentTable->level + 1;
}

void SunLuaValue::newTable() {
    lua_newtable(state);
    lua_setglobal(state, var);
}

SunLuaValue::operator int() {
    getGlobal();
    int x = lua_tointeger(state, -1);
    cleanGet();
    return x;
}

SunLuaValue::operator double() {
    getGlobal();
    double x = lua_tonumber(state, -1);
    cleanGet();
    return x;
}

SunLuaValue::operator bool() {
    getGlobal();
    bool x = lua_toboolean(state, -1);
    cleanGet();
    return x;
}

SunLuaValue::operator std::string() {
    getGlobal();
    std::string x = std::string(lua_tolstring(state, -1, NULL));
    cleanGet();
    return x;
}

SunLuaValue SunLuaValue::operator[](const char *element) {
    isTable = true;
    return SunLuaValue(state, element, true, this);
}

void SunLuaValue::operator=(const int &x) {
    if (!isTableValue) {
        lua_pushinteger(state, x);
        lua_setglobal(state, var);
    } else {
        setUpSetTable(var);
        lua_pushstring(state, var);
        lua_pushinteger(state, x);
        lua_settable(state, -3);
        cleanUpSetTable();
    }
}

void SunLuaValue::operator=(const double &x) {
    if (!isTableValue) {
        lua_pushnumber(state, x);
        lua_setglobal(state, var);
    } else {
        setUpSetTable(var);
        lua_pushstring(state, var);
        lua_pushnumber(state, x);
        lua_settable(state, -3);
        cleanUpSetTable();
    }
}

void SunLuaValue::operator=(const bool &x) {
    if (!isTableValue) {
        lua_pushboolean(state, x);
        lua_setglobal(state, var);
    } else {
        setUpSetTable(var);
        lua_pushstring(state, var);
        lua_pushboolean(state, x);
        lua_settable(state, -3);
        cleanUpSetTable();
    }
}

void SunLuaValue::operator=(const char *x) {
    if (!isTableValue) {
        lua_pushstring(state, x);
        lua_setglobal(state, var);
    } else {
        setUpSetTable(var);
        lua_pushstring(state, var);
        lua_pushstring(state, x);
        lua_settable(state, -3);
        cleanUpSetTable();
    }
}



void SunLuaValue::getGlobal() {
    if (!isTableValue)
        lua_getglobal(state, var);
    else
        setUpGetTable(var);
}

void SunLuaValue::cleanGet() {
    if (!isTableValue)
        lua_pop(state, 1);
    else
        cleanUpGetTable();
}

void SunLuaValue::setUpGetTable(const char *key) {
    if (isTableValue) { // Not a global
        parentTable->setUpGetTable(var);
        if (lua_istable(state, -1)) {
            lua_pushstring(state, key);
            lua_gettable(state, -2);
        }
    } else { // Global
        getGlobal();
        lua_pushstring(state, key);
        lua_gettable(state, -2);
    }
}

void SunLuaValue::cleanUpGetTable() {
    if (isTableValue) { // Not a global
        parentTable->cleanUpGetTable();
        lua_pop(state, 1);
    } else { // Global
        lua_pop(state, 1);
    }
}

void SunLuaValue::setUpSetTable(const char *key) {
    if (isTableValue) { // Not a global
        parentTable->setUpSetTable(var);
        if (isTable) {
            lua_pushstring(state, var);
            lua_gettable(state, -2);
        }
    } else { // Global
        getGlobal();
    }
}

void SunLuaValue::cleanUpSetTable() {
    if (isTableValue) { // Not a global
        parentTable->cleanUpSetTable();
        lua_pop(state, 1);
    }
}
