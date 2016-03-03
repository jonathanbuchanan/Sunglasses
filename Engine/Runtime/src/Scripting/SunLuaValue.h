#ifndef SUNLUAVALUE_H
#define SUNLUAVALUE_H

#include "SunLuaState.h"

#include <lua.hpp>
#include <string>
#include <vector>
#include <utility>
#include <tuple>
#include <iostream>

class SunLuaValue {
public:
    SunLuaValue(SunLuaState *s, const char *_var);
    SunLuaValue(SunLuaState *s, bool _isFunctionReturn, int _index);
    SunLuaValue(SunLuaState *s, const char *_var, bool _i, SunLuaValue *p);

    void newTable();

    operator int();
    operator double();
    operator bool();
    operator std::string();

    template<typename... T>
    void assign(T&... references) {
        assignResult(references...);
    }

    SunLuaValue operator[](const int element);
    SunLuaValue operator[](const double element);
    SunLuaValue operator[](const bool element);
    SunLuaValue operator[](const char *element);

    template<typename... T>
    SunLuaValue operator()(T... args) {
        state->getGlobal(var);
        passLuaFunctionArguments(args...);
        const int count = sizeof...(T);
        state->callFunction(count, LUA_MULTRET);
        return SunLuaValue(state, true, -1);
    }

    void operator=(const int &x);
    void operator=(const double &x);
    void operator=(const bool &x);
    void operator=(const char *x);

private:
    void getGlobal();
    void cleanGet();

    template<typename S, typename... T>
    void assignResult(S &h, T&... t) {
        int index = -state->getTop();
        h = SunLuaValue(state, true, index);
        assignResult(t...);
    }
    template<typename T>
    void assignResult(T &t) {
        int index = -state->getTop();
        t = SunLuaValue(state, true, index);
    }

    template<typename S, typename... T>
    void passLuaFunctionArguments(S h, T... t) {
        state->push(h);
        passLuaFunctionArguments(t...);
    }
    template<typename T>
    void passLuaFunctionArguments(T t) {
        state->push(t);
    }

    void setUpGetTable(const char *key);
    void cleanUpGetTable();

    void setUpSetTable(const char *key);
    void cleanUpSetTable();

    int level = 0;
    int index = -1;
    bool isTable = false;
    bool isTableValue = false;
    bool isFunctionReturn = false;
    SunLuaValue *parentTable;
    const char *var;
    SunLuaState *state;
};

#endif
