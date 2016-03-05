// Copyright 2016 Jonathan Buchanan.
// This file is part of Sunglasses, which is licensed under the MIT License.
// See LICENSE.md for details.
#include "SunLuaState.h"

namespace _SunPrivateScripting {
    template<> int get(lua_State *l, int index) {
        return lua_tointeger(l, index);
    }

    template<> double get(lua_State *l, int index) {
        return lua_tonumber(l, index);
    }

    template<> bool get(lua_State *l, int index) {
        return lua_toboolean(l, index);
    }

    template<> const char * get(lua_State *l, int index) {
        return lua_tostring(l, index);
    }


    template<> void push(lua_State *l, int value) {
        lua_pushinteger(l, value);
    }

    template<> void push(lua_State *l, double value) {
        lua_pushnumber(l, value);
    }

    template<> void push(lua_State *l, bool value) {
        lua_pushboolean(l, value);
    }

    template<> void push(lua_State *l, const char *value) {
        lua_pushstring(l, value);
    }

    template<> void push(lua_State *l, char *value) {
        lua_pushstring(l, value);
    }
}

SunLuaState::SunLuaState() {
    state = luaL_newstate();
    luaL_openlibs(state);
}

SunLuaState::SunLuaState(const char *file) {
    SunLuaState();
    luaL_dofile(state, file);
}

void SunLuaState::loadFile(const char *file) {
    luaL_dofile(state, file);
}

void SunLuaState::run(const char *code) {
    luaL_dostring(state, code);
}

void SunLuaState::getGlobal(const char *global) {
    lua_getglobal(state, global);
}

void SunLuaState::setGlobal(const char *global) {
    lua_setglobal(state, global);
}

void SunLuaState::newTable() {
    lua_newtable(state);
}

void SunLuaState::getTable(int index) {
    lua_gettable(state, index);
}

void SunLuaState::setTable(int index) {
    lua_settable(state, index);
}

int SunLuaState::getTop() {
    return lua_gettop(state);
}

int SunLuaState::getInteger(int index) {
    return lua_tointeger(state, index);
}
int SunLuaState::getInteger() {
    return getInteger(-1);
}

double SunLuaState::getNumber(int index) {
    return lua_tonumber(state, index);
}

double SunLuaState::getNumber() {
    return getNumber(-1);
}

bool SunLuaState::getBoolean(int index) {
    return lua_toboolean(state, index);
}

bool SunLuaState::getBoolean() {
    return getBoolean(-1);
}

const char * SunLuaState::getString(int index) {
    return lua_tostring(state, index);
}

const char * SunLuaState::getString() {
    return getString(-1);
}

bool SunLuaState::isInteger(int index) {
    return lua_isinteger(state, index);
}

bool SunLuaState::isInteger() {
    return isInteger(-1);
}

bool SunLuaState::isNumber(int index) {
    return lua_isnumber(state, index);
}

bool SunLuaState::isNumber() {
    return isNumber(-1);
}

bool SunLuaState::isBoolean(int index) {
    return lua_isboolean(state, index);
}

bool SunLuaState::isBoolean() {
    return isBoolean(-1);
}

bool SunLuaState::isString(int index) {
    return lua_isstring(state, index);
}

bool SunLuaState::isString() {
    return isString(-1);
}

bool SunLuaState::isTable(int index) {
    return lua_istable(state, index);
}

bool SunLuaState::isTable() {
    return isTable(-1);
}

bool SunLuaState::isFunction(int index) {
    return lua_isfunction(state, index);
}

bool SunLuaState::isFunction() {
    return isFunction(-1);
}

void SunLuaState::pushInteger(int x) {
    lua_pushinteger(state, x);
}

void SunLuaState::pushNumber(double x) {
    lua_pushnumber(state, x);
}

void SunLuaState::pushBoolean(bool x) {
    lua_pushboolean(state, x);
}

void SunLuaState::pushString(const char *x) {
    lua_pushstring(state, x);
}

void SunLuaState::pushLightUserdata(void *data) {
    lua_pushlightuserdata(state, data);
}

void SunLuaState::pushCClosure(lua_CFunction function, int upvalues) {
    lua_pushcclosure(state, function, upvalues);
}

void SunLuaState::pop(int count) {
    lua_pop(state, count);
}

void SunLuaState::pop() {
    pop(1);
}

void SunLuaState::remove(int index) {
    lua_remove(state, index);
}

void SunLuaState::callFunction(int argCount, int retCount) {
    lua_call(state, argCount, retCount);
}